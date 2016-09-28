#!/bin/bash

base_dir=$(dirname $0)
cd $base_dir

catalog=${1:-wiki-pages}

time find $catalog -type f -print0 | xargs -0 -n 1 -P 3 ./count-one.sh en
