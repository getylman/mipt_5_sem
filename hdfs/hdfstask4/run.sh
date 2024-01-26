#!/usr/bin/env bash

fsck=$(hdfs fsck / -blockId "$1" 2>/dev/null)
node=$(echo "$fsck" | awk -F '[\/ ]+' '/Block replica on/{print $6; exit}' 2>/dev/null)
local_path=$(sudo -u hdfsuser ssh hdfsuser@"$node" find / -name "*$1" 2>/dev/null)
echo "$node":"$local_path"