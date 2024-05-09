#!/bin/bash

# Set up file paths
pos_case="./pos_case.sh"
neg_case="./neg_case.sh"
pos_in_files=$(ls ../data/pos_*_in.txt)
neg_in_files=$(ls ../data/neg_*_in.txt)

# Set up test counters
pos_tests_total=$(echo "$pos_in_files" | wc -w)
pos_tests_passed=0
neg_tests_total=$(echo "$neg_in_files" | wc -w)
neg_tests_passed=0

# Run positive tests
echo "Running positive tests:"
for input_file in $pos_in_files; do
  $pos_case $input_file
  if [ $? -eq 0 ]; then
    echo "Test passed!"
    pos_tests_passed=$((pos_tests_passed+1))
  else
    echo "Test failed."
  fi
done

# Run negative tests
echo "Running negative tests:"
if [ ! -f "../data/$input_file" ]; then
    echo "Error: File '../data/$input_file' does not exist."
    exit 1
fi

for input_file in $neg_in_files; do
  $neg_case $input_file
  if [ $? -eq 0 ]; then
    echo "Test passed!"
    neg_tests_passed=$((neg_tests_passed+1))
  else
    echo "Test failed."
  fi
done

# Print test results
echo "Total positive tests: $pos_tests_total"
echo "Passed positive tests: $pos_tests_passed"
echo "Total negative tests: $neg_tests_total"
echo "Passed negative tests: $neg_tests_passed"

# Return non-zero if at least one test failed
if [ $((pos_tests_total+neg_tests_total)) -eq $((pos_tests_passed+neg_tests_passed)) ]; then
  exit 0
else
  exit 1
fi
