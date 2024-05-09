#!/bin/bash

file1="$1"
file2="$2"
attribute="$3"

if [ "$attribute" = "int" ]; then
  # Compare only integers
  if diff <(grep -Eo "[0-9]+" "$file1") <(grep -Eo "[0-9]+" "$file2") >/dev/null; then
    (exit 0)
  else
    (exit 1)
  fi
else
  # Compare entire file
  if diff "$file1" "$file2" >/dev/null; then
    (exit 0)
  else
    (exit 1)
  fi
fi
