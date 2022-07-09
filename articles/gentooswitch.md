Why I switched to Gentoo
Apr 08, 2022

A few days ago, I was curious and decided to check how long I had been running
Gentoo. If you're curious, the following command should tell you when your
filesystem was created:

    stat / | grep "Birth" | sed 's/Birth: //g' | cut -b 2-11

I switched to Gentoo ~7-8 months ago (`2021-08-18`). Since then I have learned a lot
about Linux and Gentoo itself. Although I wouldn't recommend Gentoo to
those new to Linux, I would recommend it to users who'd like total control
over their system. If you don't, I totally understand. In that case, it's
perfectly fine to run Debian. I ran Debian for a while when I had to put
my Linux-learning on hold due to an influx in schoolwork, but I still felt
that Windows had become too alien to return to.

Gentoo is an incredible distribution for those willing to learn it and
willing to put up with the installation time. I will say that the time it
takes to install Gentoo is often exaggerated. Unless you're on slower
hardware, a Gentoo install is pretty quick if you follow the handbook.
My installation took about 2 hours and leaving the system to compile
overnight.

I switched because I felt like Arch wasn't really interesting anymore.
I wanted to learn more, and I wanted to control my system even more.
The idea of configuring and compiling the entire system from source
was very appealing to me. It took me a few tries (most of the time I
began the install and was unable to finish it due to time constraints).

By far the hardest part of the install was getting X to work with Nvidia.
Configuring the kernel was surprisingly straightforward.

I will say that the default install of Gentoo used less than half the RAM
of Arch or Debian (170MB as opposed to ~300-400MB). I also like OpenRC a
lot more than SystemD. I find it to be a lot simpler; it does what
I need it to do.

Gentoo also gives the ability to use exclusively free software, even
letting you pick which licenses to use (`ACCEPT_LICENSE`).

Gentoo has put an end to my distohopping. No matter what I want to do,
Gentoo does it.
