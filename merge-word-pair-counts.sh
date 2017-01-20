#!/bin/bash

source ./globals.sh

log_name=merge_counts

function merge_counted_files
{
    local input_glob=$1
    local outdir=$2

    file_counted="${outdir}/counted.all"
    file_pairs="${outdir}/pairs.all"
    file_unique="${outdir}/unique.all"

    ./exec.py "${input_glob}" ./mergeWordPairs $file_counted $file_pairs
    sort -k1,2 $file_pairs | ./sumUniquePairs > $file_unique
    wc -l $file_unique | cut -d " " -f1 >> $file_counted
    cat $file_unique >> $file_counted
    rm $file_pairs $file_unique
}

for subdir in $(ls -d ${counted_dir}/*); do
    if [ -f ${subdir} ]; then continue; fi

    log "Merge start: ${subdir}"
    merge_counted_files "${subdir}/*[!.all]" $subdir
    log "Merge finished: ${subdir}"
done

log "Final merge start"
merge_counted_files "${counted_dir}/*/counted.all" $counted_dir
log "Final merge finished"
