#!/bin/bash

source ./globals.sh

log_name=parse_word_indexes

for subdir in $(ls -d ${split_articles_after_count_dir}/*); do
    if [ -f ${subdir} ]; then continue; fi

    log "Parse word indexes start: ${subdir}"
    indexed_articles_subdir=${indexed_articles_dir}/$(basename $subdir)
    split_articles_after_parse_subdir=${split_articles_after_parse_dir}/$(basename $subdir)
    mkdir -p $indexed_articles_subdir
    mkdir -p $split_articles_after_parse_subdir
    ./exec.py "${subdir}/*" ./parseWordIndexes $counted_articles_dir/word_pairs.counted  $indexed_articles_subdir $split_articles_after_parse_subdir
    log "Parse word indexes finished: ${subdir}"
done
