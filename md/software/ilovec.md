9-29-21

# why i love the c programming language

## why not a newer/easier language?

c is easily my favorite language of all time. even though i started with a much "easier" language (python), c
is still my favorite language for big projects. python still has it's purpose, for things like quick hacks.
despite this, i still often write scripts in c, considering most of my scripts run frequently or need to run
very quickly. c is easily the best choice for things that need to be fast.
for other languages like rust, i find that rust needs cargo
and a bunch of other things to run, and i feel like the
language is more complicated than c. c needs a compiler,
and that's about it. as long as you have access to a compiler
and the standard library you can write c code.

## small but powerful

c is a small language compared to others, and is quite simple to learn. writing good c takes time, however.
i'm certainly not a master at c, and sometimes i do write bad code. some of my scripts are hosted on this website.

## real world example

a prime example of a script that *needed* to be written in c was my script that centers my cursor on startup
of dwm. the script parses the output of xrandr, computes the values, and sets the cursor the center of the primary
monitor. this would be fast enough on it's own in most other languages, but considering that it is done during
startup of my window manager and the x server, it must be done much quicker, otherwise it may take way longer
for the cursor to actually center itself. the code is pretty convoluted, since operations like converting strings to integers
and splitting strings are a little more complicated in c than in python, but can be done much faster. you
can view the script [here](/m/center_cursor.c).
