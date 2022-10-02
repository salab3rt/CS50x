import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)


# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
@login_required
def loading():
    """Home page loader animation"""
    return render_template("loading.html", user=session["username"])


@app.route("/$", methods=["GET"])
@login_required
def index():
    """Show portfolio of stocks"""
    # Index uses AJAX to search symbols in a table

    # Handle GET requests
    if request.method == "GET":
        # Get user's stock, quantity and cash
        portfolio = db.execute(
            "SELECT symbol, SUM(quantity) as total_qty FROM transactions WHERE id = ? GROUP BY symbol ORDER BY symbol ASC;", session["user_id"])
        usr_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        # Var to hold the user cash value in stocks
        total_total = 0

        for row in portfolio:
            # On page load check user's stock update prices, this takes some time for IEX API, and so, use route "/" as a loader page
            share = lookup(row["symbol"])
            # Update every share price, when users has more than 0, to save time loading
            if (row["total_qty"] > 0):
                row.update(share)
                # Calculate shares current value
                total_share = share["price"] * row["total_qty"]
                # Sum every shares updated value
                total_total = total_total + total_share

        return render_template("index.html", portfolio=portfolio, usr_cash=usr_cash, total=total_total)

    # Handle non GET request
    if request.method != "GET":
        flash("Invalid request")
        return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    share = {}
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    # If get render page
    if request.method == "GET":
        return render_template("buy.html", cash=cash[0]["cash"])

    # If post handle the request
    elif request.method == "POST":

        # Handle empty forms
        try:
            symbl = request.form.get("symbol")
            b_qty = int(request.form.get("shares"))
        except:
            flash("Specify symbol and quantity")
            return render_template("buy.html", cash=cash[0]["cash"]), 400

        # Fetch share price
        share = lookup(symbl)

        # Handle invalid Symbols
        if share is None:
            flash("Invalid symbol")
            return render_template("buy.html", cash=cash[0]["cash"]), 400
        # Handle invalid quantities
        if b_qty < 1 or b_qty is None:
            flash("Invalid quantity")
            return render_template("buy.html", cash=cash[0]["cash"]), 400
        # Calculate total cost
        total_cost = share["price"] * b_qty

        # Get user info
        rows_usr = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        # Handle insuficient cash for the buy
        if ((rows_usr[0]["cash"] - total_cost) < 0):
            flash("Insufficient funds")
            return render_template("buy.html", cash=cash[0]["cash"]), 400

        else:
            # Update user's cash in users table
            cash[0]["cash"] -= total_cost
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash[0]["cash"], session["user_id"])
            # Update user's purchase in transactions table
            db.execute("INSERT INTO transactions (id, action, symbol, name, quantity, cost, year, month, day, time) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
                       rows_usr[0]["id"], "BUY", share["symbol"], share["name"], b_qty, total_cost, datetime.now().year, datetime.now().month, datetime.now().day, datetime.time(datetime.now()))
            # Get updated symbol transactions
            symb_hist = db.execute(
                "SELECT * FROM transactions WHERE id = ? AND symbol = ? ORDER BY year DESC, month DESC, day DESC, time DESC LIMIT 5", session["user_id"], share["symbol"])
            # Pass user history to jinja
            flash(f"Purchased: {b_qty} {symbl.upper()} shares for {usd(total_cost)}")
            return render_template("buy.html", symb_hist=symb_hist, cash=cash[0]["cash"])


@app.route("/history", methods=["GET"])
@login_required
def history():
    """Show history of transactions"""

    # Render page on GET
    if request.method == "GET":
        # Fetch user history from transactions table
        transactions = db.execute(
            "SELECT * FROM transactions WHERE id = ? ORDER BY year DESC, month DESC, day DESC, time DESC;", session["user_id"])
        return render_template("history.html", transactions=transactions, share=share)

    else:
        # Only accept GET requests
        flash("Invalid request")
        return render_template("history.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            flash("Must provide username")
            return render_template("login.html"), 400

        # Ensure password was submitted
        elif not request.form.get("password"):
            flash("Must provide password")
            return render_template("login.html"), 400

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            flash("Invalid username and/or password")
            return render_template("login.html"), 400

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["username"] = rows[0]["username"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    share = {}
    if request.method == "POST":
        symbl = request.form.get("symbol")
        share = lookup(symbl)

        # Handle invalid symbols
        if share is None:
            flash("Invalid symbol")
            return render_template("quote.html", share=share), 400

        return render_template("quote.html", share=share)

    elif request.method == "GET":
        return render_template("quote.html", share=share)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("register.html")

    elif request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            flash("Must provide username")
            return render_template("register.html"), 400

        # Ensure password was submitted
        elif not request.form.get("password"):
            flash("Must provide password")
            return render_template("register.html"), 400

        # Check if username exists in db
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username doesn't exist in db
        if len(rows) != 0:
            flash("Username already registered!")
            return render_template("register.html"), 400

        # Get password and confirmation
        pas = request.form.get("password")
        pas1 = request.form.get("confirmation")

        # Handle password confirmation mismatch
        if (pas != pas1):
            flash("Passwords don't match")
            return render_template("register.html"), 400

        # Insert in database
        else:
            usr = request.form.get("username")
            hpw = generate_password_hash(pas)
            # Insert data in users table
            db.execute("INSERT INTO users (username,hash) VALUES (?,?)", usr, hpw)

            # Get username and id
            rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
            session["user_id"] = rows[0]["id"]
            session["username"] = rows[0]["username"]

        # Redirect user to home page
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    share = {}
    # Get cash value for user
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

    # Get history to pass to javascript via jinja
    usr_stock = db.execute(
        "SELECT symbol, SUM(quantity) as quantity FROM transactions WHERE id = ? GROUP BY symbol ORDER BY symbol ASC", session["user_id"])
    if request.method == "GET":
        return render_template("sell.html", usr_stock=usr_stock, cash=cash[0]["cash"])

    elif request.method == "POST":

        # Use try to avoid error 500 on "blank" submissions
        try:
            symbl = request.form.get("symbol")
            s_qty = int(request.form.get("shares"))
        except:
            flash("Specify symbol and quantity")
            return render_template("sell.html", usr_stock=usr_stock, cash=cash[0]["cash"]), 400

        # Lookup share's data
        share = lookup(symbl)

        # Handle invalid symbols
        if share is None:
            flash("Invalid symbol")
            return render_template("sell.html", usr_stock=usr_stock, cash=cash[0]["cash"]), 400

        # Handle valid share quantity
        if s_qty < 1 or s_qty is None:
            flash("Invalid quantity")
            return render_template("sell.html", usr_stock=usr_stock, cash=cash[0]["cash"]), 400

        # Get total value of the sell
        total_cost = float(share["price"] * s_qty)

        # Get user share quantity
        rows_transactions = db.execute(
            "SELECT id, SUM(quantity), symbol FROM transactions WHERE id = ? AND symbol = ? GROUP BY symbol", session["user_id"], symbl)

        # Handle insufficient ammount of shares
        if not rows_transactions or rows_transactions[0]["SUM(quantity)"] - s_qty < 0:
            flash("Insufficient shares")
            return render_template("sell.html", usr_stock=usr_stock, cash=cash[0]["cash"]), 400

        else:
            # Calculate and update new cash value
            cash[0]["cash"] += total_cost
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash[0]["cash"], session["user_id"])

            # Insert new transaction in transactions table
            db.execute("INSERT INTO transactions (id, action, symbol, name, quantity, cost, year, month, day, time) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
                       rows_transactions[0]["id"], "SELL", share["symbol"], share["name"], -s_qty, total_cost, datetime.now().year, datetime.now().month, datetime.now().day, datetime.time(datetime.now()))

            # Get updated symbol transactions
            symb_hist = db.execute(
                "SELECT * FROM transactions WHERE id = ? AND symbol = ? ORDER BY year DESC, month DESC, day DESC, time DESC LIMIT 5", session["user_id"], share["symbol"])
            flash(f"Sold: {s_qty} {symbl.upper()} shares for {usd(total_cost)}")
            usr_stock = db.execute(
                "SELECT symbol, SUM(quantity) as quantity FROM transactions WHERE id = ? GROUP BY symbol ORDER BY symbol ASC", session["user_id"])
            return render_template("sell.html", symb_hist=symb_hist, usr_stock=usr_stock, cash=cash[0]["cash"])


@app.route("/search", methods=["GET"])
@login_required
def search():
    """Ajax handler"""
    q = request.args.get("q")
    h = request.args.get("h")
    c = request.args.get("c")
    try:
        # Handle ajax gets for index page
        if q:
            data = db.execute(
                "SELECT * FROM transactions WHERE id = ? AND symbol LIKE ? GROUP BY symbol ORDER BY symbol ASC", session["user_id"], "%" + q + "%")
            return jsonify(data)

        # Handle ajax gets for history page
        if h:
            data = db.execute("SELECT * FROM transactions WHERE id = ? AND symbol LIKE ? OR year LIKE ? OR month LIKE ? OR day LIKE ? ORDER BY time DESC, day DESC, month DESC, year DESC;",
                              session["user_id"], "%" + h + "%", "%" + h + "%", "%" + h + "%", "%" + h + "%")
            return jsonify(data)

        # Handle ajax gets for cash page
        if c:
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            cash[0]['cash'] += int(c)
            if cash[0]['cash'] > 25000:

                cash[0].update({"msg": "Don't be greedy!"})
                cash[0].update({"cash": 0})
                c = []

            else:
                db.execute("UPDATE users SET cash = ? WHERE id = ?", cash[0]['cash'], session["user_id"])
                cash[0].update({'msg': "Added: " + usd(int(c))})

            return jsonify(cash)

        # If no arguments in GET
        else:
            cash = []
            return jsonify(cash)

    except:
        return render_template("cash.html"), 400


@app.route("/manage", methods=["GET", "POST"])
@login_required
def change_pass():

    if request.method == "GET":
        return render_template("manage.html")

    elif request.method == "POST":

        # Ensure old password was submitted
        if not request.form.get("old_pass"):
            flash("Must provide current password")
            return render_template("manage.html"), 400

        # Ensure new password was submitted
        elif not request.form.get("password"):
            flash("Must provide new password")
            return render_template("manage.html"), 400

        # Ensure new password was re-submitted
        elif not request.form.get("confirmation"):
            flash("Must repeat new password")
            return render_template("manage.html"), 400

        # Hanle new and old pass macthes
        elif request.form.get("old_pass") == request.form.get("confirmation"):
            flash("Current and new password can't match")
            return render_template("manage.html"), 400

        oldpass = request.form.get("old_pass")
        check_old = db.execute("SELECT hash FROM users WHERE id= ?", session["user_id"])
        # Check if old password and password in db match
        oldpass1 = check_password_hash(check_old[0]["hash"], oldpass)

        # Handle wrong old password
        if (oldpass1 == False):
            flash("Wrong password")
            return render_template("manage.html"), 400

        new_pass = request.form.get("password")
        new_pass1 = request.form.get("confirmation")

        # Check if new pass and confirmation match
        if (new_pass != new_pass1):
            flash("Passwords don't match")
            return render_template("manage.html"), 400

        else:
            # Update user new pass in users table
            db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(new_pass), session["user_id"])
            session.clear()
            flash("Password changed, Login again")
            # Prompt login
            return render_template("login.html")


@app.route("/cash", methods=["GET"])
@login_required
def cash():

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

    return render_template("cash.html", cash=cash)

