var darkMode = false;

function dark_mode() {
    if (!darkMode) {
        document.body.style = `
        background-color: #000000;
        color: #b9b4b4;
        `;

        var x = document.querySelectorAll("code");
        var i;
        for (i = 0; i < x.length; i++)
            x[i].style.backgroundColor = "#a9a9a94b";
        
        document.getElementById('darkmode-btn').innerText = "Light Mode"
        darkMode = true;
    } else {
        document.body.style = `
        background-color: #f6f2f2;
        color: #444;
        `;

        var x = document.querySelectorAll("code");
        var i;
        for (i = 0; i < x.length; i++)
            x[i].style.backgroundColor = "#d6d2d2";

        document.getElementById('darkmode-btn').innerText = "Dark Mode"
        darkMode = false;
    }
}