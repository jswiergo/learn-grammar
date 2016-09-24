#!/bin/bash

base_dir=$(dirname $0)
cd $base_dir

tmux new-session -d -s run_relex ./loop-relex.sh
