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
        let response = await fetch('/search?q=' + input.value);
        let data = await response.json();
        if (data.length > 0) {
            let tr = '';
            let html = '';
            for (const rows in data) {
                /* Populate each <td> according to each key in the JSON retieved */
                symb = '<td>' + data[rows].symbol + '</td>';
                name = '<td>' + data[rows].name + '</td>';
                /* On page load, current share price is updated,
                pass those values to the page */
                for (const row in upd_data) {
                    if (upd_data[row].symbol == data[rows].symbol) {
                        shares = '<td>' + upd_data[row].total_qty + '</td>';

                        price = '<td>' + upd_data[row].price.toLocaleString(
                            'en-US', { style: 'currency', currency: 'USD' }) + '</td>';

                        tot = upd_data[row].total_qty * upd_data[row].price;

                        total = '<td>' + tot.toLocaleString(
                            'en-US', { style: 'currency', currency: 'USD' }) + '</td>';
                    }
                }
                /* populate HTML <tr> */
                html += '<tr>' + symb + name + shares + price + total + '</tr>';
            }
            /* If the AJAX request returned a non empty JSON file
            it changes the old table to d-none, in order to hide the old table so it lists the
            search response. This was done, so, when index.html loads, or the search form imput is cleared
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
