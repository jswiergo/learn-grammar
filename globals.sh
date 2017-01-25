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
wiki_stripped_dir=${articles_dir}/wiki-stripped
wiki_pages_dir=${articles_dir}/1-wiki-pages
split_articles_dir=${articles_dir}/2-split-articles
counted_articles_dir=${articles_dir}/3-counted-articles
wiki_pages_after_count_dir=${articles_dir}/4-wiki-pages
split_articles_after_count_dir=${articles_dir}/5-split-articles
indexed_articles_dir=${articles_dir}/6-indexed-articles
split_articles_after_parse_dir=${articles_dir}/7-split-articles
articles_disjuncts_dir=${articles_dir}/8-articles-disjuncts
indexed_articles_after_parse_dir=${articles_dir}/9-indexed-articles

# Logging
function log
{
    local log_entry=$1
    time=$(date "+%Y-%m-%d %H:%M:%S")
    echo $time $log_entry >> ${logs_dir}/${log_name}.log
}
