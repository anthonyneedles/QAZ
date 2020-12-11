#!/bin/sh

###############################################################################
# git-hash-name-copy.sh
#
# Copies given files with a new name of style "old-name_X_Y", where X = 'C' for 
# a clean repo or 'D' for a dirty repo, and Y is the short git hash.
#
# The git information read from the current HEAD. A "clean" repo is defined
# as one that does not have unstaged/uncommitted changes.
#
# Args: $1 = files to perform script on
###############################################################################

[ -z "$1" ] && echo "No argument supplied" && exit 1

# update the index
git update-index -q --refresh

# _C_ for clean, _D_ for dirty
state='C'

# check for any unstaged changes in working tree
if ! git diff-files --quiet --
then
    state='D'
fi

# check for any uncommitted changed in index
if ! git diff-index --quiet --cached HEAD --
then
    state='D'
fi

# get 7-digit short hash
hash=$(git rev-parse --short HEAD)

for f in "$@"; do
    cp -- "$f" "${f%.*}"_"$state"_"$hash"."${f##*.}"
done

