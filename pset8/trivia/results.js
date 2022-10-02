function check(event)
{
    var triggerObj = event.srcElement;

    if (triggerObj.textContent == "Giant Squid")
    {
        triggerObj.style.cssText = `background-color: #32a852; transition: background-color 0.25s linear;`;
        chk = document.getElementById("check1");
        chk.style.cssText = `color: #32a852; display: block; font-weight: 600;`;
        chk.textContent = "CORRECT";
    }
    else
    {
        triggerObj.style.cssText = `background-color: #f5f5f5; transition: background-color 0.25s linear; animation: buttons 3s;`;
        chk = document.getElementById("check1");
        chk.style.cssText = `color: #f23d3d; display: block; color: ease; font-weight: 600;`;
        chk.textContent = "INCORRECT";
    }
}

function check_1()
{
    var answer = document.getElementById("answer").value;


    if (answer == "195")
    {
        chk = document.getElementById("check2");
        chk.style.cssText = `color: #32a852; display: block; color: ease; font-weight: 600;`;
        chk.textContent = "CORRECT";
    }
    else
    {
        document.getElementById("check2").style.cssText = `color: #f23d3d; display: block; color: ease; font-weight: 600;`;
        chk = document.getElementById("check2");
        if (answer < "195")
        {
            chk.textContent = "INCORRECT, HIGHER!";
        }
        else if (answer > "195")
        {
            chk.textContent = "INCORRECT, LOWER!";
        }

        document.getElementById("q2").reset();
    }
}