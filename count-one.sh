#!/bin/bash

base_dir=$(dirname $0)
cd $base_dir

source ./config.sh

filename=$1
lang=$2

# Split the filename into two parts
base=`echo $filename | cut -d \/ -f 1`
rest=`echo $filename | cut -d \/ -f 2-6`

# Create directories if needed
mkdir -p $(dirname "$split_dir/$rest")
mkdir -p $(dirname "$counted_dir/$rest")
mkdir -p $(dirname "$finished_dir/$rest")

# Sentence split the article itself
cat "$filename" | $splitter -l $lang >  "$split_dir/$rest"

# Counting word pairs pipeline
cat "$split_dir/$rest" |
    (while read line; do
        echo -e $line |
        nc $relex_host $relex_port;
    done) |
    ./filterWordPairs |
    ./countWordPairs > "$counted_dir/$rest"

# Move article to the finished-queue
mv "$split_dir/$rest" "$finished_dir/$rest"
rm "$filename"
