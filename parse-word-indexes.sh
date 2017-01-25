#!/bin/bash

source ./globals.sh

log_name=parse_word_indexes

for subdir in $(ls -d ${split_articles_after_count_dir}/*); do
    if [ -f ${subdir} ]; then continue; fi

    log "Parse word indexes start: ${subdir}"
    mkdir -p ${indexed_articles_dir}/${subdir}
    mkdir -p ${split_articles_after_parse_dir}/${subdir}
    ./exec.py "${subdir}/*" ./parseWordIndexes ${indexed_articles_dir}/${subdir} ${split_articles_after_parse_dir}/${subdir}
    log "Parse word indexes finished: ${subdir}"
done
