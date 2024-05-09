#!/bin/bash

check_file_exists() {
    if [ ! -f "$1" ] || [ ! -f "$2" ]; then
        if [ "$3" == "-v" ] || [ "$3" == "--verbose" ]; then
            echo 'Файл не найден.'
        fi
        exit 2
    fi
}

extract_numbers() {
    local file_numbers=""
    for word in $(cat "$1"); do
        if [[ $word =~ ^[+-]?[0-9]+$ ]]; then
            file_numbers="$file_numbers $word"
        fi
    done
    echo "$file_numbers"
}

check_file_exists "$1" "$2" "$3"

file1_numbers=$(extract_numbers "$1")
file2_numbers=$(extract_numbers "$2")

if [ "$file1_numbers" == "$file2_numbers" ]; then
    if [ "$3" == "-v" ] || [ "$3" == "--verbose" ]; then
        echo 'Содержимое совпало'
    fi
    exit 0
else
    if [ "$3" == "-v" ] || [ "$3" == "--verbose" ]; then
        echo 'Содержимое не совпало'
    fi
    exit 1
fi

