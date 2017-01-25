#!/bin/bash

source ./globals.sh

log_name=merge_counts

function merge_counted_files
{
    local input_glob=$1
    local outdir=$2
    local name=$3

    file_counted="${outdir}/${name}.counted"
    file_pairs="${outdir}/${name}.pairs"
    file_unique="${outdir}/${name}.unique"

    ./exec.py "${input_glob}" ./mergeWordPairs $file_counted $file_pairs
    sort -k1,2 $file_pairs | ./sumUniquePairs > $file_unique
    wc -l $file_unique | cut -d " " -f1 >> $file_counted
    cat $file_unique >> $file_counted
    rm $file_pairs $file_unique
}

for subdir in $(ls -d ${counted_articles_dir}/*); do
    if [ -f ${subdir} ]; then continue; fi

    log "Merge start: ${subdir}"
    merge_counted_files "${subdir}/*" $counted_articles_dir $(basename $subdir)
    log "Merge finished: ${subdir}"
done

log "Final merge start"
rm -f ${counted_articles_dir}/word_pairs.counted
merge_counted_files "${counted_articles_dir}/*.counted" $counted_articles_dir "word_pairs"
log "Final merge finished"
