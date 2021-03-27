var html_head = 
`
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="/article.css">
    <title>
`;
var darkMode = false;

function make_article(title, author, date, text) {
    var final_text = html_head + title.trim() + " - Hasan Zahra's Website</title>\n";
    final_text += "</head>\n<body>\n<header class=\"article-header\">\n";
    final_text += "<h1 class=\"article-title\">" + title.trim() + "</h1>\n";
    final_text += "<p class=\"article-date\">" + date.trim() + "</p>\n";
    final_text += "<p class=\"article-author\"> By " + author.trim() + "</p>\n<hr>\n</header>\n";
    var real_text = text.replace("\n", "<br><br>");
    final_text += real_text;
    final_text += "</body>\n<script src=\"/index.js\"></script>";
    final_text += "</html>";
    document.body.innerHTML = final_text;
}


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