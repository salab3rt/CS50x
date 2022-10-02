/*https://www.codegrepper.com/code-examples/javascript/debounce+code+javascript*/
const debounce = (fn, delay) => {
    let timer;
    return function() {
        clearTimeout(timer);
        timer = setTimeout(fn, delay);
    };
};

/* https://codeburst.io/throttling-and-debouncing-in-javascript-b01cad5c8edf */
const throttle = (func, limit) => {
    let inThrottle
    return function() {
        const args = arguments
        const context = this
        if (!inThrottle) {
            func.apply(context, args)
            inThrottle = true
            setTimeout(() => inThrottle = false, limit)
        }
    }
}

/* Set timeout to disable cash button after clicked */
function coin() {
    let flash = document.getElementById('flash');
    let coin = document.getElementById("coin");
    var button = document.getElementById("btnusr1");

    button.addEventListener('click', function() {

        flash.innerHTML = '<br>';
        /* Animate coin and disable button on click */
        button.setAttribute("disabled", "");
        coin.setAttribute("class", "loader_coin1");

        /* Reset coin animation and set a timeout 2seconds for the button to become active again */
        setTimeout(function() {
            button.removeAttribute("disabled");
            coin.setAttribute("class", "loader_coin");
        }, 2000);
    });
}

/* Generate random (1000 - 10000) cash to add to the user */
function cash_rand() {

    let input = document.getElementById("btnusr1");

    /* Generate cash on click */
    /* debounce async function to avoid multiple clicks, probably redundant since coin() disables cash button
    but if button was pressed multiple times at start, it fetched multiple times,
    leading to crash */
    input.addEventListener('click', debounce(async function() {

        /* random ammount function */
        const random = Math.floor(Math.random() * 9000) + 1000;

        /* async request to backend with the random ammount*/
        let response = await fetch('/search?c=' + random);
        let data = await response.json();
        let flash = document.getElementById('flash');
        let upd_cash = document.getElementById('btnusr1')

        /* if no cash was retrieved (user cash + random > 25000) */
        if (data[0].cash == 0) {
            flash.innerHTML = '<div class="alert alert-warning mb-0 text-center list" id="flash"role="alert">' +
                data[0].msg + '</div>';
        } else {
            /* if random was added to user cash, pass value to HTML */
            flash.innerHTML = '<div class="alert alert-warning mb-0 text-center list" id="flash"role="alert">' +
                data[0].msg + '</div>';
            /* since jinja only runs on page load, and this is a async request,
            cash value needed to be formatted in JS function */
            upd_cash.innerHTML = 'Cash: ' + data[0].cash.toLocaleString(
                'en-US', { style: 'currency', currency: 'USD' });
        }
    }, 500));

}