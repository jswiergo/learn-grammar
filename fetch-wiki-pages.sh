#!/bin/bash

source ./globals.sh

log_name=fetch_wiki_pages

function download_file
{
    local url=$1
    local filename=$2

    log "Download start: $url"
    exit_code=$(curl -s -o $filename -w "%{http_code}" $url)

    if [ "$exit_code" == "200" ]; then
        status="OK"
    else
        status="FAILED"
    fi
    log "Download $status: $url"
    echo $status
}

function process_wiki_file
{
    local filename=$1

    log "Scrubbing start: $filename"
    cat $filename | bunzip2 | $wiki_scrubber
    log "Scrubbing finished: $filename"

    log "Cleaning start: $filename"
    cd $base_dir
    cd $wiki_stripped_dir
    ${wiki_cleaner/\{lang\}/$language}
    cd $base_dir
    log "Cleaning end: $filename"

    log "Separation start: $filename"
    mkdir -p $wiki_pages_dir
    ./separateFiles.py $wiki_stripped_dir $wiki_pages_dir
    log "Separation end: $filename"
}

function wiki_dump_part_name
{
    local part=$1

    file_part=${wiki_dump_file/\{part\}/$part}.xml
    cat $wiki_dump_index | grep $file_part | cut -d '"' -f2 | grep -v rss
}

mkdir -p $articles_dir
mkdir -p $wiki_stripped_dir
cd $articles_dir

wiki_dump_index=${wiki_dump_file/\{part\}/-index.html}

# download wikipedia dumps index file
# TODO: catch errors
download_file $wiki_dump_url $wiki_dump_index >> /dev/null

# download partial dumps
downloaded_parts=""
if [ "$max_wiki_parts" != "" ]; then
    for part in $(seq 1 $max_wiki_parts); do
        file_part=$(wiki_dump_part_name $part)
        if [ "$file_part" == "" ]; then
            break
        fi
        status=$(download_file ${wiki_dump_url}${file_part} $file_part)
        if [ "$status" != "OK" ]; then
            break
        fi
        downloaded_parts="OK"
        process_wiki_file $file_part
    done
fi

# download full dump if necessary
if [ "$downloaded_parts" != "OK" ]; then
    file_part=$(wiki_dump_part_name)
    status=$(download_file ${wiki_dump_url}${file_part} $file_part)
    if [ "$status" == "OK" ]; then
        process_wiki_file $file_part
    fi
fi
