#!/bin/bash

language=en
max_wiki_parts=2

# Relex
relex_dir=/home/jacek/github/relex

splitter=${relex_dir}/src/split-sentences/split-sentences.pl
wiki_scrubber=${relex_dir}/src/perl/wiki-scrub.pl
wiki_cleaner=${relex_dir}/src/wiki-clean-\{lang\}.sh
wiki_alpha=${relex_dir}/src/wiki-alpha.sh

# Wikipedia
wiki_latest_dump_url=https://dumps.wikimedia.org/\{lang\}wiki/latest/
wiki_latest_dump_file=\{lang\}wiki-latest-pages-articles\{part\}

# Catalogs
logs_dir=logs
articles_dir=articles
wiki_pages_dir=${articles_dir}/wiki_pages
split_dir=${articles_dir}/split-articles
finished_dir=${articles_dir}/finished-articles
counted_dir=${articles_dir}/counted-articles
