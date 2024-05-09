#!/bin/bash

check_file_exists() {
    if [ ! -f "$1" ]; then
        exit "$2"
    fi
}

compare_files() {
    if ! func_tests/scripts/comparator.sh "$1" "$2"; then
        exit 1
    fi
}

if [ "$#" -lt 4 ]; then
    exit 100
fi

file_stream_in=$1
file_stream_out_expect=$2
file_stream_args=$3
file_stream_out_file_expect=$4
file_stream_out_file_actual="out_file.txt"
file_stream_out_actual="out.txt"

check_file_exists "$file_stream_in" 50
check_file_exists "$file_stream_out_expect" 50
check_file_exists "$file_stream_args" 50
check_file_exists "./app.exe" 40

read -ra args < <(cat "$file_stream_args")
if ! ./app.exe "${args[@]}" < "$file_stream_in" > "$file_stream_out_actual"; then
    exit 2
fi

./app.exe b2t "$file_stream_out_file_expect"
./app.exe b2t "$file_stream_out_file_actual"

compare_files "$file_stream_out_expect" "$file_stream_out_actual"
compare_files "$file_stream_out_file_expect" "$file_stream_out_file_actual"

exit 0

