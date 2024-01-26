#!/usr/bin/env bash

output=$(curl --silent -i "http://mipt-master:50070/webhdfs/v1$1?op=OPEN&length=10")
echo "$output" | awk -F '[\/: ]+' '/^Location:/{print $3;}' 2>/dev/null