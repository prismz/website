<!--META DATE 9-29-21 -->
<!--META CATEGORY software -->

<h3>writing a static site generator</h3>

## why not markdown?

    when i started my new website, i needed a new and better way to generate articles.
    most people use markdown and have a program to convert it to html and add a header and footer,
    but i don't want to learn markdown. i already know html, so why not just have the article
    be in html?


## how it works

    each article is stored in a source directory, with no html boilerplate - just
    the body of the article and the title and some comments at the top for metadata. a python
    script goes through each file in the directory, performing the following actions:

    <ul class="alist">
        <li type="1">parse all comments containing metadata</li>
        <li type="1">parse the title</li>
        <li type="1">parse each &lt;h4&gt; tag into a content list</li>
        <li type="1">convert each &lt;h4&gt; to have an id</li>
        <li type="1">add header and footer</li>
    </ul>


## the result

    i'm actually quite happy with how the site turned out. it
    looks simple, and a pretty short python script generates
    a rather complete looking site. it may be mostly plain text,
    but the way the formatted html looks in the files and
    rendered in the browser is honestly much better than i
    expected. 


<p class="strikethrough">the only downside is that there is (currently)
    no way to create the homepage, so it must be updated
    manually for each new article. this is a fairly simple
    addition, and one i plan to implement soon.



    i recently implemented the above mentioned feature, so now the entire site can
    be generated using a single script call.



## the code

    you can view the most up-to-date version of the code 
    <a href="/gen.py">here</a>.

