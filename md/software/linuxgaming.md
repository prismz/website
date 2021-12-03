<!--META DATE 10-15-21 -->
<!--META CATEGORY software -->

<h3>tips and tricks for gaming on linux</h3>

## the main obstacles

    gaming on linux can be difficult. often times you will
    find yourself frustrated because a game *could* work
    on linux, but doesn't because of drm or anticheat.


## configuring your system's open file limit

    if using wine/proton to play games, many games will
    crash because most distributions do not allow enough files
    to be open. to fix this, edit /etc/security/limits.conf
    and add the following line:

# End of file
* hard nofile 1048576


    and restart your computer. only do this if you find your games
    are crashing with a message along the lines of eventfd: 
    too many open files.



    *
        note: this config file may be overwritten if you run etc-update without
        paying attention, so this option will need to be added again
        if this happens. if your games suddenly stop working after etc-update,
        this may be why.
    *


## kernel options

    some games (and a lot of software) don't work without user namespaces,
    so it's a good idea to enable them even if you're not gaming on linux.
    the option can be found under general setup - namespaces support - user namespace.
    if you're having issues with chromium (or anything based on it) this may also fix that 
    as well.


## no internet access in games

    some games don't behave properly and complain about having
    no internet access. for these games (ex. osu), you need the package net-libs/gnutls
    (or the equivalent package on your distro, for example lib32-gnutls
    on arch).


## font issues

    some games don't render fonts very well by default. installing
    the microsoft corefonts may help (media-fonts/corefonts
    on gentoo).


## custom proton versions

    gloriouseggroll's custom version of proton works quite
    well and i recommend using it. i've used it for quite some
    time and as long as you remember to download a newer version 
    every now and then you'll be up to date. you can find
    it on github <a href="https://github.com/GloriousEggroll/proton-ge-custom">
    here</a>.


## optimized kernels

    things like custom kernels and gaming optimizer software
    never really worked for me, but you can try them if you'd
    like. an example "gaming kernel" would be <a href="https://xanmod.org/">
    xanmod</a>. i personally prefer just using a lighter custom
    linux kernel.


## kvm and passthroughs

    many people use iommu/kvm (kernel virtual machine)
    and a gpu passthrough to run games on windows with
    native linux performance. i've never done this,
    but many people say it works very well. the arch
    wiki has a page <a href="https://wiki.archlinux.org/title/KVM">here</a>
    and there are plenty of videos on youtube.


## summary

    all of these things may seem complicated, but most
    games work just fine natively on linux. often
    times you just download a game and run it. i remember
    how good it was just a year or so ago, and things are even
    better now. if the thought of being limited from games with
    drm/anticheat is scaring you away, consider dual booting.
    truth be told you'd be better off not playing those games
    in the first place ;)

