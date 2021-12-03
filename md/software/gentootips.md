9-30-21

# gentoo linux tips and tricks

*note: this page assumes you have some experience
with linux and that you know what hardware you
have in your computer. if not, i highly suggest
gaining some experience or checking your specs
before running gentoo.*

gentoo linux is my favorite linux distribution for my use
case, second place going to arch, and third going to debian.
being source based with things like use flags and a more
complicated package manager (portage) than most distributions,
some say gentoo has a steep learning curve. with linux experience
and a capable computer you can run gentoo rather easily, even
on exotic hardware (though kernel configuration may be difficult).

## prerequisites

all you really need is basic knowledge and a computer 
capable of compiling. while you can install gentoo on
a slower or low spec machine, it may take much longer
to compile everything.

## installation tips

make sure to follow the
[gentoo handbook](https://wiki.gentoo.org/wiki/Handbook:Main_Page)
when installing, and only use 3rd party installation videos or
instructions as secondary resources. this is because everyone's
system will be different, and using someone else's configurations
may not be best for you, or may not even work on your hardware.

decide what kind of system you want. do you want a desktop
environment? do you want to use systemd or openrc? pulseaudio
or alsa? are you running gentoo on a server? do you need
new software? consider these things when configuring portage.

## kernel configuration

this is what caused me the most problems starting out,
since i have a rather old and obscure IDE/SATA controller,
which i had to dig around for. if you're having problems,
if you're running a linux system already (can be a livecd), 
run lspci -k to see various hardware and the 
corresponding kernel modules. look up the kernel modules 
if anything isn't working. i got kernel panics because 
because my IDE controller wasn't supported, so the linux kernel
couldn't find or mount my root filesystem (kernel panic: unable
to mount root filesystem). when running any custom compiled linux
kernel, make sure you have things like that enabled first.
you can worry about things non-essential to boot later, but 
it is rather difficult to get non-essential things working
when your computer can't boot. when i tried to install kiss 
linux i had the same problem, and you can read my reddit post 
[here](https://www.reddit.com/r/kisslinux/comments/mljopc/kiss_linux_kernel_panic_unable_to_mount_root_fs/).

it's a good idea to read the help section for each option.
you also may be able to get away with not using an initramfs
if you don't need to load modules on startup. it's a good idea
to start with an initramfs and try removing it later, so build
one at first.

*note: make sure to use -j(number of cpu cores) when 
compiling the kernel to reduce build times.*

## cleaning the system

since gentoo is a source based distribution, the source code downloaded
to install packages will cause the root filesystem to become full faster
than on other binary distributions. using eclean you can 
remove the extra files on your system.

    # all of this should be done as root using sudo or doas

    # to clean packages
    eclean-dist -d

    # to remove n number of old kernels 
    eclean-kernel -n [number]

## useful software

a list of useful software:
- [app-portage/gentoolkit](https://wiki.gentoo.org/wiki/Gentoolkit) - portage utils
- [app-portage/cpuid2cpuflags](https://packages.gentoo.org/packages/app-portage/cpuid2cpuflags) - get CPU\_FLAGS

## misc

if you want to use a cross compiler on gentoo for whatever reason (typically operating system development),
gentoo provides a package you can use to set it up (sys-devel/crossdev). you can read the wiki page
[here](https://wiki.gentoo.org/wiki/Embedded_Handbook/General/Creating_a_cross-compiler#crossdev).

if you want to get your -march right the first time, use [this page](https://wiki.gentoo.org/wiki/Safe_CFLAGS)
to get it correct for your cpu. trust me, i had to recompile my entire system because i used 
-march=native instead of -march=bdver2.

