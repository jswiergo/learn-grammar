#!/bin/bash

base_dir=$(dirname $0)
cd $base_dir

source ./config.sh

for subdir in $(ls -d ${counted_dir}/*); do
    if [ -f ${subdir} ]; then continue; fi

    echo $(date) "Merge ${subdir}"
    ./merger.py "${subdir}/*[!.all]" ./mergeWordPairs "${subdir}/counted.all" "${subdir}/pairs.all"
    sort -n -k1,2 "${subdir}/pairs.all" | ./sumUniquePairs > "${subdir}/unique_pairs.all"
    wc -l "${subdir}/unique_pairs.all" | cut -d " " -f1 >> "${subdir}/counted.all"
    cat "${subdir}/unique_pairs.all" >> "${subdir}/counted.all"
    rm ${subdir}/*pairs.all
done

echo $(date) "Final merge"
./merger.py "${counted_dir}/*/counted.all" ./mergeWordPairs "${counted_dir}/counted.all" "${counted_dir}/pairs.all"
sort -n -k1,2 "${counted_dir}/pairs.all" | ./sumUniquePairs >> "${counted_dir}/unique_pairs.all"
wc -l "${counted_dir}/unique_pairs.all" | cut -d " " -f1 >> "${counted_dir}/counted.all"
cat "${counted_dir}/unique_pairs.all" >> "${counted_dir}/counted.all"
rm ${counted_dir}/*pairs.all

echo $(date) "Finished"