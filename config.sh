#!/bin/bash

# Language code for language used in experiment. At the moment
# following languages are supported: en fr gu hi lt pl tl
lang=en

# Maximum number of Wikipedia articles dump files to download.
# See: https://dumps.wikimedia.org/enwiki/latest/
# The file enwiki-latest-pages-articles.xml.bz2 containing all articles
# has more than 13 GB compressed. If you want to download all articles
# comment out this variable, otherwise set maximum number of parts.
max_wiki_parts=1

# Root catalog of Relex sources. We are using only a few scripts from
# Relex sources.
relex_dir=/home/jacek/github/relex
