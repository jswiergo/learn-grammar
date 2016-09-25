#!/bin/bash

base_dir=$(dirname $0)
cd $base_dir

source ./config.sh

for subdir in $(ls -d ${counted_dir}/*); do
    echo "Merge ${subdir}"
    time ./merger.py ./mergeWordPairs "${subdir}/*[!.all]" > ${subdir}/counted.all
    echo
done

echo "Final merge"
time ./merger.py ./mergeWordPairs "${counted_dir}/*/*[!.all]" > ${counted_dir}/counted.all
