#!/bin/sh

alacritty -T "command_menu" -e sh -c '
  echo "
xrandr --output HDMI-1 --mode 1920x1200 --right-of eDP-1
setxkbmap -layout us,cz -option grp:alt_shift_toggle
xmodmap -e '\''clear lock'\'' & xmodmap -e '\''keycode 9 = Escape NoSymbol Escape'\'' & xmodmap -e '\''keycode 66 = Escape NoSymbol Escape'\''
systemctl --user start status_bar.service
poweroff
reboot
" | fzf --height=20 --border --ansi | ${SHELL:-/bin/sh}
'
