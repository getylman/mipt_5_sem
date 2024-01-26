#!/usr/bin/env bash

file_size=$1
block_size=$(hdfs getconf -confKey dfs.blocksize)

additional_storage=$(echo "($file_size - 1) / $block_size * $block_size" | bc)

echo "$additional_storage"