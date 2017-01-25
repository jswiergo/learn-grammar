#!/bin/bash

# called from $articles_dir
source ../../globals.sh

log_name=count_articles

filename=$1
echo $filename

# Logging info
start_miliseconds=$(($(date +%s%N)/1000000))
file_size=$(stat -c %s "$articles_dir/$filename")

# Split the filename into two parts
base=`echo $filename | cut -d \/ -f 1`
rest=`echo $filename | cut -d \/ -f 2-6`

# Create directories if missing
mkdir -p $(dirname "$split_articles_dir/$rest")
mkdir -p $(dirname "$counted_articles_dir/$rest")
mkdir -p $(dirname "$wiki_pages_after_count/$rest")
mkdir -p $(dirname "$split_articles_after_count/$rest")

# Sentence split the article itself
cat "$articles_dir/$filename" | $splitter -l $lang >  "$split_articles_dir/$rest"

# Counting word pairs pipeline
cat "$split_articles_dir/$rest" | $base_dir/parseWordPairs 2>/dev/null | $base_dir/countWordPairs > "$counted_articles_dir/$rest"

# Move wiki pages and split articles to next stage directory
mv "$articles_dir/$filename" "$wiki_pages_after_count/$rest"
mv "$split_articles_dir/$rest" "$split_articles_after_count_dir/$rest"

# Log status
end_miliseconds=$(($(date +%s%N)/1000000))
total_miliseconds=$(( $end_miliseconds - $start_miliseconds ))
total_seconds=$(echo "print $total_miliseconds/1000.0" | python)

log "$filename: (size=$file_size, time=$total_seconds): OK"
