#!/bin/bash

source ./globals.sh

log_name=parse_disjuncts

for subdir in $(ls -d ${indexed_articles_dir}/*); do
    if [ -f ${subdir} ]; then continue; fi

    log "Parse disjuncts start: ${subdir}"
    articles_disjuncts_subdir=${articles_disjuncts_dir}/$(basename $subdir)
    indexed_articles_after_parse_subdir=${indexed_articles_after_parse_dir}/$(basename $subdir)
    mkdir -p $articles_disjuncts_subdir
    mkdir -p $indexed_articles_after_parse_subdir
    ./exec.py "${subdir}/*" ./parseDisjuncts $counted_articles_dir/word_pairs.mi  $articles_disjuncts_subdir $indexed_articles_after_parse_subdir
    log "Parse disjuncts finished: ${subdir}"
done
