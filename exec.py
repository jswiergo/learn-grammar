#!/usr/bin/python

import glob
import os
import subprocess
import sys

# This program allows execution command without limitation on number of filenames
# passed as arguments. The xargs limit 128 Kb for command parameters is insufficient.

if len(sys.argv) < 3:
    print "Executes program with files that matches given glob pattern appended as program additional parameters."
    print "Usage: %s <glob_pattern> <program_to_execute> <program_params>...." % sys.argv[0]
    exit(1)

params = sys.argv[2:]

for f in glob.glob(sys.argv[1]):
    params.append(os.path.abspath(f))

out = subprocess.check_output(params)
sys.stdout.write(out)
