#!/bin/bash

###############################################################################
# create-version.sh
#
# Takes version header template and populates variables with build information.
#
# The git information read from the current HEAD. A "clean" repo is defined
# as one that does not have unstaged/uncommitted changes.
#
# Args: $1 = file to perform script on (REQUIRED)
#       $2 = QAZ board type            (REQUIRED)
#       
###############################################################################

[ -z "$1" ] && echo "No input file supplied" && exit 1
[ -z "$2" ] && echo "No board given"         && exit 1

# update the index
git update-index -q --refresh

# 0x0 for clean, 0xF for dirty (the upper nibble of the 4th hash byte)
state_char='0'

# "CLEAN" for clean, "DIRTY" for dirty
state_str='CLEAN'

# check for any unstaged changes in working tree
if ! git diff-files --quiet --
then
    state_char='F'
    state_str='DIRTY'
fi

# check for any uncommitted changed in index
if ! git diff-index --quiet --cached HEAD --
then
    state_char='F'
    state_str='DIRTY'
fi

# get 7-digit short hash
hash="$(git rev-parse --short HEAD)"
hash=${hash^^}

# populate all the variables in the template
sed -e "s/\${CHAR_GIT_HASH}/0x${state_char}${hash:0:1}, 0x${hash:1:2}, 0x${hash:3:2}, 0x${hash:5:2}/" \
    -e "s/\${GIT_HASH}/\"${hash}\"/" \
    -e "s/\${GIT_STATE}/\"${state_str}\"/" \
    -e "s/\${BOARD}/\"$2\"/" \
    $1.in >| $1
