#!/bin/bash

base_dir=$(dirname $0)
cd $base_dir

source ./config.sh
log_file=${logs_dir}/fetch_wiki_pages.log

# TODO: move to config.sh
function log
{
    local log_entry=$1
    time=$(date "+%Y-%m-%d %H:%M:%S")
    echo $time $log_entry >> $log_file
}

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


function wiki_dump_part_name
{
    local part=$1

    file_part=${wiki_dump_file/\{part\}/$part}.xml
    cat $wiki_dump_index | grep $file_part | cut -d '"' -f2 | grep -v rss
}

wiki_dump_url=${wiki_latest_dump_url/\{lang\}/$language}
wiki_dump_file=${wiki_latest_dump_file/\{lang\}/$language}
wiki_dump_index=${wiki_dump_file/\{part\}/-index.html}

# download wikipedia dumps index file
# TODO: catch errors
download_file $wiki_dump_url $wiki_dump_index >> /dev/null

# download partial dumps
downloaded_parts=""
if [ "$max_wiki_parts" != "" ]; then
    for part in $(seq 1 $max_wiki_parts); do
        file_part=$(wiki_dump_part_name $part)
        status=$(download_file ${wiki_dump_url}${file_part} $file_part)
        if [ "$status" == "OK" ]; then
            downloaded_parts="OK"
            # TODO: call scrub.pl
        else
            break
        fi
    done
fi

# download full dump if necessary
if [ "$downloaded_parts" != "OK" ]; then
    echo "full"
fi
