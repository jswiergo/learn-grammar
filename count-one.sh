#!/bin/bash

base_dir=$(dirname $0)
cd $base_dir

source ./config.sh
log_file=${logs_dir}/count_articles.log

filename=$1
lang=${2:-en}

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
mkdir -p $(dirname "$relex_out_dir/$rest")
rm -f "$relex_out_dir/$rest.failed"

# Sentence split the article itself
cat "$filename" | $splitter -l $lang >  "$split_dir/$rest"


# Counting word pairs pipeline
cat "$split_dir/$rest" |
    while read line; do
        # Save relex output into temporary file
        echo -e $line | nc $relex_host $relex_port > "$relex_out_dir/$rest"

        # Check if relex output is not broken
        correct_end_line=$(tail -n1 "$relex_out_dir/$rest" | egrep "NO PARSES|END OF SENTENCE")
        if [ "$correct_end_line" ]; then
            cat "$relex_out_dir/$rest"
        else
            echo $line > "$relex_out_dir/$rest.failed"
            break
        fi
    done |
    ./filterWordPairs |
    ./countWordPairs > "$counted_dir/$rest"

# Exit if relex failed
if [ -f "$relex_out_dir/$rest.failed" ]; then
    echo "$filename: FAILED" >> $log_file
    exit 1
fi

# Move article to the finished-queue
mv "$split_dir/$rest" "$finished_dir/$rest"
rm "$filename"

# Remove temporary file
rm "$relex_out_dir/$rest"

# Log status
end_miliseconds=$(($(date +%s%N)/1000000))
total_miliseconds=$(( $end_miliseconds - $start_miliseconds ))
total_seconds=$(echo "print $total_miliseconds/1000.0" | python)

echo "$filename: (size=$file_size, time=$total_seconds): OK" >> $log_file
