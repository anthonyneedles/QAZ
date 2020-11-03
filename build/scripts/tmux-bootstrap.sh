#!/bin/sh

PROJECT_ROOT="$(cd $(dirname "$0"); pwd)/.."
SESSION="$1"

# will stop here is session already exists
tmux new-session     -d -s ${SESSION} || exit 1

# first window: development with serial debugger terminal
WINDOW0="dev-debug"
tmux rename-window   -t    ${SESSION} ${WINDOW0}
tmux split-window    -h -t ${WINDOW0}
tmux select-pane     -t 1
tmux send-keys       -t ${WINDOW0} "sudo screen /dev/ttyUSB0 115200" C-m
tmux select-pane     -t 0

# attach to new session (with forced 256 colors)
tmux -2 attach-session -t ${SESSION}
