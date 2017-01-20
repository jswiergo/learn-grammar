#!/bin/bash

# Base directory
base_dir=$(dirname $0)
cd $base_dir
base_dir=$(readlink -f .)

source ./config.sh

# Relex scripts
splitter=${relex_dir}/src/split-sentences/split-sentences.pl
wiki_scrubber=${relex_dir}/src/perl/wiki-scrub.pl
wiki_cleaner=${relex_dir}/src/perl/wiki-clean-${lang}.sh
wiki_alpha=${relex_dir}/src/perl/wiki-alpha.sh

# Wikipedia dumps
wiki_dump_url=https://dumps.wikimedia.org/${lang}wiki/latest/
wiki_dump_file=${lang}wiki-latest-pages-articles\{part\}

# Catalogs
logs_dir=${base_dir}/logs
articles_dir=${base_dir}/articles/${lang}
wiki_pages_dir=${articles_dir}/wiki-pages
wiki_stripped_dir=${articles_dir}/wiki-stripped
split_dir=${articles_dir}/split-articles
finished_dir=${articles_dir}/finished-articles
counted_dir=${articles_dir}/counted-articles

# Logging
function log
{
    local log_entry=$1
    time=$(date "+%Y-%m-%d %H:%M:%S")
    echo $time $log_entry >> ${logs_dir}/${log_name}.log
}
