#!/bin/bash

check_file_exists() {
    if [ ! -f "$1" ]; then
        exit "$2"
    fi
}

if [ "$#" -lt 2 ]; then
    exit 100
fi

file_stream_in=$1
file_stream_args=$2

check_file_exists "$file_stream_in" 50
check_file_exists "$file_stream_args" 50
check_file_exists "./app.exe" 40

read -ra args < <(cat "$file_stream_args")
if ./app.exe "${args[@]}" < "$file_stream_in" > out.txt; then
    exit 1
else
    exit 0
fi

