#!/bin/bash

base_dir=$(dirname $0)
cd $base_dir

time find ${wiki_pages_dir} -type f -print0 | xargs -0 -n 1 -P 3 ./count-article-word-pairs.sh
