/*https://www.codegrepper.com/code-examples/javascript/debounce+code+javascript*/
const debounce = (fn, delay) => {
    let timer;
    return function() {
        clearTimeout(timer);
        timer = setTimeout(fn, delay);
    };
};

function search() {

    let input = document.querySelector('input');
    let old = document.getElementById('data');

    /* Event listner on input, for a search form,
    debounce async function to avoid multiple request before server could respond, whiche led to state 500 */
    input.addEventListener('input', debounce(async function() {
        let response = await fetch('/search?h=' + input.value);
        let data = await response.json();
        if (data.length > 0) {
            let tr = '';
            let html = '';
            for (const rows in data) {
                /* Populate each <td> according to each key in the JSON retieved */
                action = '<td>' + data[rows].action + '</td>';
                symb = '<td>' + data[rows].symbol + '</td>';
                name = '<td>' + data[rows].name + '</td>';
                shares = '<td>' + Math.abs(data[rows].quantity) + '</td>';
                price = Math.abs(data[rows].cost / data[rows].quantity);
                share_price = '<td>' + price.toLocaleString(
                    'en-US', { style: 'currency', currency: 'USD' }) + '</td>';

                /* sell share quantity is stored as negative values, and the total cost comes as negative
                so need to use Math.abs to get an unsigned cost value */
                total = Math.abs(data[rows].cost)
                cost = '<td>' + total.toLocaleString(
                    'en-US', { style: 'currency', currency: 'USD' }) + '</td>';

                date = '<td>' + data[rows].year + '/' + data[rows].month + '/' + data[rows].day + ' ->' + data[rows]
                    .time + '</td>';

                /* BUY actions will list as green text */
                if (data[rows].action == "BUY") {
                    /* Populate each table row, with <td> */
                    html += '<tr class="buy">' + action + symb + name + shares + share_price + cost + date +
                        '</tr>';
                } else {
                    /* SELL actions will come has yellow text */
                    html += '<tr class="sell">' + action + symb + name + shares + share_price + cost + date +
                        '</tr>';
                }
            }
            /* If the AJAX request returned a non empty JSON file
            it changes the old table to d-none, in order to hide the old table so it lists the
            search response. This was done, so, when history.html loads, or the search form imput is cleared
            the default table is shown, instead of a blank table */
            old.setAttribute("class", "text-light d-none");
            document.getElementById('qdata').setAttribute("class", "text-light");
            document.getElementById('qdata').innerHTML = html;
        } else {
            /* Returned JSON is empty, show old table, so the <table> isnt blank
            and Hide the query table */
            old.setAttribute("class", "text-light");
            document.getElementById('qdata').setAttribute("class", "text-light d-none");
        }
    }, 500));
}