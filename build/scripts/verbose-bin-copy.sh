#!/bin/bash

###############################################################################
# verbose-bin-copy.sh
#
# Copies given file with a new name, which includes input flags and git repo
# dirty/clean state and short hash.
#
# Any input flags will prepend the git info, separated by underscores.
#
# The git information read from the current HEAD. A "clean" repo is defined
# as one that does not have unstaged/uncommitted changes.
#
# Args: $1     = file to perform script on (REQUIRED)
#       $@[1:] = Variable list of flags    (OPTIONAL)
#       
###############################################################################

[ -z "$1" ] && echo "No input file supplied" && exit 1

# grab file name, remove from arg list
file=$1
shift

# update the index
git update-index -q --refresh

# _C_ for clean, _D_ for dirty
state='CLEAN'

# check for any unstaged changes in working tree
if ! git diff-files --quiet --
then
    state='DIRTY'
fi

# check for any uncommitted changed in index
if ! git diff-index --quiet --cached HEAD --
then
    state='DIRTY'
fi

# get 7-digit short hash
hash=$(git rev-parse --short HEAD)

# create string of flags, if there are any
flags=""
for flag in "$@"
do
    flags+="${flag}_"
done

cp -- "$file" "${file%/*}/${flags}${state}_${hash}.${file##*.}"
