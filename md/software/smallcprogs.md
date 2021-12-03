11-16-21

# a collection of small c programs i've written

## portage-installed.c

this program does exactly what it sounds like - lists
all programs installed through portage. i wrote it
because `equery list "*"` took ~11 seconds to
run, while my code runs instantly. all it does is list installed
packages so you'll still need to use equery for listing @world
and other things. you can find the source [here](/m/portage-installed.c).

## perms2num.c

`perms2num` takes a permission code (like `rw-rwx-rw` from `ls -l`
and converts it into an octal. codes can be passed as arguments or piped in (`ls -l | ./perms2num`).
you can find the source [here](/m/perms2num.c).

## center\_cursor.c

center cursor does what it sounds like. it takes output from xrandr
and converts it into coordinates and makes a call to `xdotool` to move
and click the mouse in the center of the primary monitor. you can find the source [here](/m/center_cursor.c).
do note that for it to work you need `xrandr` and `xdotool`.

## tmfmt.c

formats a time from seconds into a readable string. i use this in my `.bashrc` to
measure how long the last command took. you can find the source [here](/m/tmfmt.c).

## mh.c

`mh` stands for make header, and it is used to make a header and c source code file
using a default (or specified) include guard. i wrote this because i don't like writing boilerplate.
for example, `./mh test` would create the files `test.c` and `test.h`
with the following contents:

    /* test.h */
    #ifndef TEST_H
    #define TEST_H

    #endif

    /* test.c */
    #include "test.h"
    
you can find the source [here](/m/mh.c).

## asciitable.c

i'm forgetful so i tend to forget my ascii chart, so i wrote a simple program to
print one. you can find the source [here](/m/asciitable.c).

## eatram.c

does what it sounds like. it will eat all your ram. your pc will likely
hang until linux kills the process. this one is totally pointless but
fun. you can find the source [here](/m/eatram.c).
