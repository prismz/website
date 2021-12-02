# playing classic doom on a modern pc

## options

you have many options to play doom, and it may be a good
idea to pick a certain one based on what you want. you will
need an iwad file for doom, and you can simply look around
for an iwad file, or use the <code>doom1.wad</code> file provided by 
<a href="https://www.dosgamers.com/dos/dos-games/doom-heretic-hexen">dosgamers</a>
(ignore that it says dos or windows 10, the <code>doom1.wad</code> file
works on my linux and windows machine). for a direct download link,
click [here](https://distro.ibiblio.org/slitaz/sources/packages/d/doom1.wad).

## chocolate doom

chocolate doom is a doom source port designed to be as close
to the original doom as possible. the wiki can be found
[here](https://www.chocolate-doom.org/wiki/index.php/Chocolate_Doom).
it is licensed under gplv2, so it is free
software. almost every single linux distribution has
it in the repos so it can be installed from there if
you like. note that when you launch chocolate doom for the first
time, you should launch it from the command line so you can provide the iwad
file. i personally wrote a shell script in <code>/usr/local/bin</code>
to launch it with the iwad each time:

    #!/bin/sh
    chocolate-doom -iwad (path)

## gzdoom

gzdoom is an opengl port of the original doom, based on the older
[gldoom](https://doomwiki.org/wiki/GlDoom). it is more like a modern
fps, with jumping and your typical 3d mouse movement. it can be found in
most linux repos, and is quite simple to install. for windows, you can download it
[here](https://www.zdoom.org/downloads). just like chocolate
doom, it's a good idea to launch it from the command line for the first time
if you need to provide the path to the iwad file.

## which to choose

if you want an experience closest to the original doom,
use chocolate doom. if you want a modern style rendition,
use gzdoom. other versions exist, and if you don't like
either of these, you can look at those.
