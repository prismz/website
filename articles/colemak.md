I switched to Colemak about 2 months ago. I feel much more comfortable when typing,
and programming doesn't put nearly as much strain on my wrists as it did when i used QWERTY.
Installing Colemak was actually quite easy on both my Linux and Windows systems.

I use Vim, and I haven't rebound any keys. It's not that bad to use to be honest. The
reason I didn't rebind any keys is because a lot of Vim commands are pneumonics, and typing
seemingly random letters slowed me down, defeating the entire purpose of Vim keybinds.

If you play games, do not be worried, as most games seem to read input directly from the keyboard,
meaning no rebinding required for native Linux games. Games running through Proton or Wine will have
to either have all their keys rebound, or you will have to temporarily switch to QWERTY when playing
them (which is what I recommend).

You can set Colemak as your keyboard layout in X by adding the command to your `~/.xinitrc`.
Add the following line for just Colemak:

    exec setxkbmap colemak &

And the following for Colemak and QWERTY (Colemak being the default - You can swap the order for the other way around):

    exec setxkbmap -layout colemak,us -option grp:win_space_toggle &

To toggle the layouts press the Super (Windows) key and the space bar. This keybind can be changed,
and you can read the [Arch Wiki Page](https://wiki.archlinux.org/title/Xorg/Keyboard_configuration#Using_setxkbmap) for more information.
