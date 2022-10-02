/* Show slider value function */
function slider(slider) {
    var slider = document.getElementById("slider");
    var output = document.getElementById("qty");
    output.innerHTML = slider.value;
    /* When slider is moved shows it's value on page */
    slider.oninput = function() {
        output.innerHTML = this.value;
    }
}

/* Limit slider value, by select form Symbol's quantity */
function slider_maxv() {
    let input = document.getElementById("inputform1");
    let output = document.getElementById("slider");
    console.log(usr_stock);
    output.disabled = true;
    /* Get input from select form option */
    input.addEventListener("input", async function() {
        let response = input.value;
        /* usr_stock var is set in sell.html */
        /* Iterate through usr_stock */
        for (const [key, value] of Object.entries(usr_stock)) {
            /* If select input matches a symbol in usr_stock,
            set Slider MAX value = the symbol's quantity */
            if (value.symbol == response) {
                output.disabled = false;
                output.setAttribute("max", value.quantity);
                /* reset slider current value to 1 */
                output.value = 1;
                /* update slider value on page */
                slider(slider);
                return;
            }
            /* if JSON response is empty, disable the slider, set it to 0, and update it's value */
            if (response == "None") {
                output.disabled = true;
                output.value = 0;
                slider(slider);
                return;
            }
        }

    });
}