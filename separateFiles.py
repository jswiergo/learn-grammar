#!/usr/bin/python

import sys
import os

MAX_ARTICLES_IN_SUBDIR = 5000

if len(sys.argv) != 3:
    print "Usage: %s <source dir> <destination dir>...." % sys.argv[0]
    exit(1)

source_dir = sys.argv[1]
split_dir = sys.argv[2]

dest_subdir_number = 1
dest_subdir_count = 0

dest_subdir = os.path.join(split_dir, str(dest_subdir_number))
if not os.path.isdir(dest_subdir):
    os.mkdir(dest_subdir)

for subdir in os.listdir(split_dir):
    if os.path.isdir(os.path.join(split_dir, subdir)):
        try:
            subdir_number = int(subdir)
            if subdir_number > dest_subdir_number:
                dest_subdir_number = subdir_number
        except:
            pass

dest_subdir = os.path.join(split_dir, str(dest_subdir_number))
dest_subdir_count = len(os.listdir(dest_subdir))

for article in os.listdir(source_dir):
    if dest_subdir_count >= MAX_ARTICLES_IN_SUBDIR:
        dest_subdir_number += 1
        dest_subdir_count = 0
        dest_subdir = os.path.join(split_dir, str(dest_subdir_number))
        os.mkdir(dest_subdir)
    
    os.rename(os.path.join(source_dir, article), os.path.join(dest_subdir, article))
    dest_subdir_count += 1
