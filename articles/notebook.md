A notebook program written entirely in POSIX shell
Jun 5, 2022

I like to keep notebook-style directories on my computer for various
reasons. I use them to journal and keep track of files, among other
things.

I decided that to learn POSIX shell, I'd rewrite my old notebook application
that I wrote in Haskell a while back. The code may not be the most perfect 
POSIX shell code, but I think that it's fairly easy to understand.

A "notebook" is just a directory with a list of files. All files with names
that are just numbers without an extension are treated as pages. When you
use the program to access a notebook, it checks to see if any pages have been
removed, and fixes the order of the pages.

For example, a notebook with 4 pages should look as follows: (1, 2, 3, 4).
If the user decides to delete a page (let's say page 2), the notebook
now looks like (1, 3, 4). The program will check for this and fix it to
where it properly displays as (1, 2, 3) after the removal of a page.

Usage is as follows:

    notebook [notebook path] [action] [page (if needed)]

`action` must be one of the following:

1. `new` - create and edit a new page using $EDITOR.
2. `edit [page]` - edit an existing page using $EDITOR.
3. `view [page]` - view a page using $PAGER.
4. `remove [page]` - remove a page.
5. `info` - print information on the notebook (size, number of entries, etc.)
6. `backup` - create a `.tar.gz` backup in the current directory of the notebook.

## Source
You can view the source [here](/media/notebook).

## Installation

To install the program, just run the following commands:

    wget https://hasanzahra.xyz/media/notebook
    chmod +x notebook
    cp notebook /usr/local/bin/  # This must be run as root.

You can change `/usr/local/bin/` to anywhere on `$PATH`, but I recommend
that location for programs and scripts not installed by the package manager.
