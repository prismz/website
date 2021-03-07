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

