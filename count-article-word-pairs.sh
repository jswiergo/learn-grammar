#!/bin/bash

source ./global.sh

log_name=count_articles

filename=$1

# Logging info
start_miliseconds=$(($(date +%s%N)/1000000))
file_size=$(stat -c %s "$filename")

# Split the filename into two parts
base=`echo $filename | cut -d \/ -f 1`
rest=`echo $filename | cut -d \/ -f 2-6`

# Create directories if needed
mkdir -p $(dirname "$split_dir/$rest")
mkdir -p $(dirname "$counted_dir/$rest")
mkdir -p $(dirname "$finished_dir/$rest")

# Sentence split the article itself
cat "$filename" | $splitter -l $language >  "$split_dir/$rest"

# Counting word pairs pipeline
cat "$split_dir/$rest" | ./parseWordPairs 2>/dev/null | ./countWordPairs > "$counted_dir/$rest"

# Move article to the finished-queue
mv "$split_dir/$rest" "$finished_dir/$rest"
rm "$filename"

# Log status
end_miliseconds=$(($(date +%s%N)/1000000))
total_miliseconds=$(( $end_miliseconds - $start_miliseconds ))
total_seconds=$(echo "print $total_miliseconds/1000.0" | python)

log "$filename: (size=$file_size, time=$total_seconds): OK"
