#!/usr/bin/python

import glob
import os
import subprocess
import sys

if len(sys.argv) < 3:
    print "Executes merger program with files that matches given glob pattern passed as arguments."
    print "Usage: %s <merger_program> <glob_pattern>" % sys.argv[0]
    exit(1)

params = []
params.append(sys.argv[1])
for f in glob.glob(sys.argv[2]):
    params.append(os.path.abspath(f))

out = subprocess.check_output(params)
sys.stdout.write(out)

