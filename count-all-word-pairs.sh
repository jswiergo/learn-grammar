#!/bin/bash

source ./globals.sh

cd $articles_dir
time find $(basename $wiki_pages_dir) -type f -print0 | xargs -0 -n 1 -P 1 $base_dir/count-article-word-pairs.sh
