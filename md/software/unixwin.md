10-1-21

# a unix-like environment on windows

## coreutils

the windows 10 command prompt sucks. it provides
few commands, and the ones it does provide are 
clunky and much worse than their \*nix counterparts.
there are two options:

- use an entirely new shell program</li>
- install a windows compatible version of \*nix like coreutils</li>


i opted for the first option, since a full \*nix-like shell
is much better in general than the command prompt, for things like
aliases, custom prompts, etc. if you just need coreutils, i'm 
sure you can find the coreutils online (or write your own if you want a challenge).
an example from the windows package manager chocolately 
is the [gnuwin32 coreutils](https://community.chocolatey.org/packages/gnuwin32-coreutils.install) package.

## shell

i chose to use cygwin for my shell, but there are others. what is 
annoying is that by default cygwin's home directory is different than your own,
so you need to navigate to your windows home path to use the shell there.
other than that, it is nearly perfect and i just added a line to the .bashrc 
to start in my real home by default.

## compiler

if you need gcc instead of whatever compiler microsoft uses,
you can use [mingw](https://sourceforge.net/projects/mingw/)
(minimalist gnu on windows), but be warned that some of the typical features 
you'd use in c don't work. for example, pwd.h is missing, 
and to format size\_t you can't use %zu for some reason. 
i don't know if these are the fault of mingw, but to be fair their implementation 
is nearly perfect, and the worst thing you may have to do for cross platform code 
is some preprocessor checks. see example [here](/m/platform.h).

