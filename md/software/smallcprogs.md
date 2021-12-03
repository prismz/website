11-16-21

# a collection of small c programs i've written

## portage-installed.c

    this program does exactly what it sounds like - lists
    all programs installed through portage. i wrote it
    because <code>equery list "*"</code> took ~11 seconds to
    run, while my code runs instantly. all it does is list installed
    packages so you'll still need to use equery for listing @world
    and other things. you can find the source <a href="/m/portage-installed.c">here</a>.


## perms2num.c

    <code>perms2num</code> takes a permission code (like <code>rw-rwx-rw</code> from <code>ls -l</code>
    and converts it into an octal. codes can be passed as arguments or piped in (<code>ls -l | ./perms2num</code>).
    you can find the source <a href="/m/perms2num.c">here</a>.


## center_cursor.c

    center cursor does what it sounds like. it takes output from xrandr
    and converts it into coordinates and makes a call to <code>xdotool</code> to move
    and click the mouse in the center of the primary monitor. you can find the source <a href="/m/center_cursor.c">here</a>.
    do note that for it to work you need <code>xrandr</code> and <code>xdotool</code>.


## tmfmt.c

    formats a time from seconds into a readable string. i use this in my <code>.bashrc</code> to
    measure how long the last command took. you can find the source <a href="/m/tmfmt.c">here</a>.


## mh.c

    <code>mh</code> stands for make header, and it is used to make a header and c source code file
    using a default (or specified) include guard. i wrote this because i don't like writing boilerplate.
    for example, <code>./mh test</code> would create the files <code>test.c</code> and <code>test.h</code>
    with the following contents:
<pre>
/* test.h */
#ifndef TEST_H
#define TEST_H

#endif
</pre>

<pre>
/* test.c */
#include "test.h"
</pre>
    
    you can find the source <a href="/m/mh.c">here</a>.



## asciitable.c

    i'm forgetful so i tend to forget my ascii chart, so i wrote a simple program to
    print one. you can find the source <a href="/m/asciitable.c">here</a>.


## eatram.c

    does what it sounds like. it will eat all your ram. your pc will likely
    hang until linux kills the process. this one is totally pointless but
    fun. you can find the source <a href="/m/eatram.c">here</a>.

