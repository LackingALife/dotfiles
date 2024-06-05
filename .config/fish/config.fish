if status is-interactive
    # Commands to run in interactive sessions can go here
end

set fish_greeting 

export SDL_VIDEODRIVER=wayland
export _JAVA_AWT_WM_NONREPARENTING=1
export QT_QPA_PLATFORM=wayland
export XDG_CURRENT_DESKTOP=sway
export XDG_SESSION_DESKTOP=sway

alias timkb="setxkbmap -layout us,pt -variant colemak,"
alias peterkb="setxkbmap -layout us,pt"
alias resetbar="sh ~/.config/waybar/waybar.sh"

thefuck --alias | source

zoxide init fish | source

function bind_bang
    switch (commandline -t)[-1]
        case "!"
            commandline -t -- $history[1]
            commandline -f repaint
        case "*"
            commandline -i !
    end
end

function bind_dollar
    switch (commandline -t)[-1]
        case "!"
            commandline -f backward-delete-char history-token-search-backward
        case "*"
            commandline -i '$'
    end
end

function fish_user_key_bindings
    bind ! bind_bang
    bind '$' bind_dollar
end

