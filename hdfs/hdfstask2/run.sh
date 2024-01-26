#!/usr/bin/env bash

file=$1

hdfs dfs -get "$file" /tmp/file.txt
head -c 10 /tmp/file.txt
rm /tmp/file.txt
