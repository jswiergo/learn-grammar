#!/bin/bash

base_dir=$(dirname $0)
cd $base_dir

catalog=$1

time find $catalog -type f -exec ./count-one.sh {} en \;
