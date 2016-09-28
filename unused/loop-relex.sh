#!/bin/bash

base_dir=$(dirname $0)
cd $base_dir

source ./config.sh

log_file=${logs_dir}/run_relex.log
check_period=30

unset TMUX

function log
{
    log_time=$(date +"%Y-%m-%d %H:%M:%S")
    echo $log_time $* | tee -a $log_file
}

function kill_previous_session
{
    # if previous session exsists capture recent output before killing
    tmux_session=$(tmux ls 2>/dev/null | egrep "^relex_any")
    if [ "$tmux_session" ]; then
        log "previous session output: " $tmux_session

        tmux capture-pane -t relex_any
        tmux show-buffer | tee -a $log_file
        tmux delete-buffer

        tmux kill-session -t relex_any
        log "previous session killed: " $tmux_session
    fi
}

function start_relex_server
{
    tmux new-session -d -s relex_any "cd ${relex_dir}; ./${relex_server}; sleep 1000d"
    log "relex server started"
}

function is_relex_server_working
{
    relex_process=$(ps -ax | grep java | grep -i relex.server | grep any)
    if [ "$relex_process" == "" ]; then
        log "relex server died"
        return 1
    else
        log "relex server working - OK"
        return 0
    fi
}

while true; do
    log "restart relex server"

    kill_previous_session
    start_relex_server

    # periodically check if relex server is still working
    sleep ${check_period}
    while is_relex_server_working; do
        sleep ${check_period}
    done

done
