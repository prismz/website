9-29-21

# c programming styles - the one i use and why

there are many c programming styles. c programming style
refers to things like bracket placement, how you declare functions,
spaces around operators, using parenthesis for sizeof(), comments, etc.

## brackets
some use brackets on the same line, some use them on the next.
i personally add them on the same line, unless declaring a function,
which i'll discuss later. for example:

    if (condition) {
        func1();
        func2();
    }

it is important to note that when a conditional only has one statement,
i don't use parenthesis. for example:

    if (condition)
        func1();

i do this because i feel like having brackets on their own like
clutters up the codebase unnecessarily, and adds extra lines.
unless you're a programmer from the 70s being paid per line of code,
why add extra lines within functions?

## whitespace

i use spaces instead of tabs, a tab being 4 spaces. some prefer
using 8 instead, the linux kernel being a primary example. i
don't use whitespace around parenthesis, but do around operators
and commas. conditionals have a space before the parenthesis,
but functions don't. for example:

    int var = 2 + 4;

    if (condition1 || condition2)
        statement();

when structuring a file, i avoid using more than one blank
line in a row. for example:

    #include <stdio.h>

    int
    main(void)
    {
    
    }

## function declaration
to declare a function, i put the return type and modifiers
on one line, the function name and arguments on the next,
and then the opening bracket on the next line. this is
done to avoid functions with a lot of arguments taking
up too much space on a line. for example:

    int
    add(int a, int b)
    {
        return a + b;
    }

if a function has no arguments, always put `void`
in the parenthesis. for example:

    /* does nothing */
    void
    noargs(void)
    {
        return;
    }

## comments

comments that fit on one line are denoted using `/* comment */`.
comments that take up more than one line have an opening line, the contents
of the comment (each line beginning with a \*), and then the line closing
the comment. for example:

    /* this is a one line comment */
    
    /*
     * this comment takes up
     * multiple lines
     * so it uses this style
     */
    
    int
    function(int a)
    {
        return a + 2;  /* inline comments have 2 spaces */
    }

this is done automatically by vim for multiline comments,
and i don't use `//` because each line requires it.
many editors handle multiline comments the same way.
inline comments have 2 spaces to separate the code from the comment.

## why?
i've developed this style over time, taking inspiration
from other styles, copying what i liked and leaving what
i didn't like. i like the linux kernel's code style, but
the 8 width tabs are not my favorite. i liked how suckless
declares functions and styles brackets, so i copied their style.

at the end of the day it all comes down to personal preference,
and if you really prefer a style you should use it. just use what
works best for you (as long as you're keeping consistent with your
codebase, so don't use your own style if it clashes with the
style a project already uses). i'd use the linux kernel's style
if i were to contribute code out of respect for maintainers. some people may hate the way i declare functions and
others may love it. avoid *big* sins and you should be fine.
these are things that are obvious - don't have a bunch of blank lines
in the middle of a file, match whatever indentation you're using, etc.
it is also worth noting that this isn't really very important when 
first starting out, and you should really focus on the basics first.
