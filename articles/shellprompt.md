Why I use a very simple shell prompt
Jul 09, 2022

These days many people use a fancy shell prompt.
I've tried fancy shell prompts, and I actually used
one for a while. Later on, however, I ran into a few
problems with my large prompt.

1. When working with a terminal on a screen with
    little available space, longer shell prompts
    would wrap onto the next line.

2. When writing longer commands (typically with something
    like executing `make` and then calling valgrind with
    options, which I did quite often as a C programmer),
    the commands would wrap onto the next line. This isn't
    really a problem unless you're using a very small terminal,
    but I use smaller terminals.

3. I use the terminal a lot. I'd probably say that `st` is my
    most used program besides maybe `firefox-bin`. I always have
    terminals open, even if I'm not directly using one. I leave
    `mutt`, `htop`, and `cmus` open on another monitor. What this
    means is that larger (especially multi-line) prompts require
    you to clear the screen quite often. This is trivial, but it
    becomes annoying having to scroll back up to look at the output
    of a previous command, when you only ran it a couple commands
    ago.

If you think that I'm being unreasonable by complaining about line
breaks, most project style standards enforce a line length limit of
80 characters, a primary example being the
[Linux kernel](https://www.kernel.org/doc/html/v4.10/process/coding-style.html#breaking-long-lines-and-strings).

The following is an example of my shell prompt over time:

    [(exit code) (time taken) (git) user@hostname path/to/cwd] $
    [path/to/cwd] $
    [bold(path/to/cwd)] $
    path/to/cwd
    %

I stopped showing the current directory because I found that after
changing directories I would almost always `ls` anyway, which would
almost always let me know where I was. In the rare case that I didn't
know (or had left a terminal open and forgotten where I was), `pwd` is
fairly easy to type (though this is in my opinion the main downside
of removing the current directory from your prompt).

I also found that having a shell prompt with a consistent width was
very beneficial for scripting. You can look at my build of `st` as
an example. Using [Luke Smith's script](https://github.com/LukeSmithxyz/st/blob/master/st-copyout)
to copy the output of the previous command worked much better when
using a consistent shell prompt.

I've also found that it lets me focus better on what I'm actually
doing. The more crowded my shell is the less I feel I actually have
any space to type commands. You can't make aliases for everything,
so it helps to have the extra terminal real estate.

If you really want a little more information, you could change the
color of the `%` to indicate the result of the previous command or
something else. If it's red, the previous command failed. If it's
bolded, you're root, etc.

If you don't use the terminal much, or just want the extra information,
then you can do as you'd like. But I've found that the more I used
the terminal, the smaller I made my shell prompt.
