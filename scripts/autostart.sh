#!/bin/sh

xrandr --output HDMI-1 --left eDP-1
#setxkbmap -layout us,cz -option grp:alt_shift_toggle
setxkbmap -layout us,cz -option grp:ctrls_toggle
#setxkbmap -layout us
xmodmap -e 'clear lock'
xmodmap -e 'keycode 9 = Escape NoSymbol Escape'
xmodmap -e 'keycode 66 = Escape NoSymbol Escape'
systemctl --user restart status_bar.service
#nitrogen --restore
xsetroot -solid "#181818"
picom &
dunst &
gnome-keyring-daemon --start --components=secrets &
