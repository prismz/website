# make sure dirs are in path
PATH=$PATH:/$HOME/.local/bin
PATH=$PATH:/sbin/

function timer_start {
  timer=${timer:-$SECONDS}
}

function timer_stop {
  timer_show=$(($SECONDS - $timer))
  unset timer
}

trap 'timer_start' DEBUG
PROMPT_COMMAND=timer_stop

# [bolded current_dir_basename user@system - x seconds] bolded_lambda
PS1='[\[\e[0;1m\]\W\[\e[0m\] \u@\h - $(tmfmt ${timer_show})] \[\e[0;1m\]λ\[\e[0m\] '

# ls aliases
alias ll='ls -lh'
alias la='ls -a'
alias lla='ls -lah'
alias l1='ls -1'
alias sl='ls' # for typos

# gentoo aliases
alias ek='cd /usr/src/linux/ && doas make menuconfig'
alias k='cd /usr/src/linux'

# portage aliases
alias e='doas emerge --ask'
alias es='doas emerge --search'
alias er='doas emerge --deselect'
alias eq='~/dev/portage-utils/portage-installed'
alias eu='doas emerge --ask --update --deep --with-bdeps=y --newuse @world'
alias ed='doas emerge --depclean --ask'
alias wc='watch -n 3 doas genlop -nci'
alias wn='doas genlop -ci'
alias whatscompiling='echo use wn or wc - wc to watch - wn for one off use.'
alias ec='doas genlop -t'

# aurinstall aliases (enable on arch)
# alias y='aurinstall install'
# alias ys='aurinstall search'
# alias update='doas pacman -Syu && aurinstall update'

# gentoo aliases
alias kernel='cd /usr/src/linux'
alias makeconf='doas nvim /etc/portage/make.conf'
alias portage='cd /etc/portage'

# config file aliases
alias bashrc='nvim ~/.bashrc && source ~/.bashrc'
alias vimrc='nvim ~/.vimrc'

# command replacements
alias cls='clear'
alias h='htop'
alias c='cmus'
alias sx='cd && startx'
alias rb_='doas reboot'
alias murder='killall -9'
alias obliterate='srm -rv'
alias quick-obliterate='srm -rlv'
alias ssh='TERM="xterm" ssh'
alias addkey='gpg --recv-keys'
alias python='python3'
alias up='uptime'
alias ntpsync='doas ntpdate -b pool.ntp.org; doas hwclock -w'

alias rm='rm -rfv'
alias mv='mv -v'
alias cp='cp -rv'

alias neo='neofetch'
alias hackerman='clear; neofetch'

alias mullvad='doas openvpn --config /etc/openvpn/openvpn.conf; doas /etc/openvpn/update-resolv-conf.py'
alias fixdns='doas /etc/openvpn/update-resolv-conf.py'
alias amiconnected='curl https://am.i.mullvad.net/connected'

# youtube-dl aliases
alias ytdl='youtube-dl'
alias yt='youtube-dl'
alias ytda='youtube-dl -x --audio-format mp3'

# directory aliases
alias mus='cd ~/aud/mus/'

# set neovim as editor
EDITOR=nvim
export EDITOR=nvim
