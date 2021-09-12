[[ -f ~/.Xresources ]] && xrdb -merge -I$HOME ~/.Xresources

exec ~/dev/script/center_cursor &
exec ns &
#exec feh --bg-center ~/hdd1/img/wallpapers/1610273314356.jpg & 
exec xrandr --output DVI-D-0 --mode 2560x1080 --pos 2560x0 --rotate normal --output HDMI-0 --primary --mode 2560x1080 --pos 0x0 --rotate normal --output DP-0 --off --output DP-1 --mode 1920x1080 --pos 5120x0 --rotate normal &
exec dwm


#exec xdotool mousemove 0 0 & 

#exec xmonad
#exec ~/dev/hzwm/hzwm
#exec ~/dev/srwm/srwm
#exec ~/dev/hzwm/tinywm

