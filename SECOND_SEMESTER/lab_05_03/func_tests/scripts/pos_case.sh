#!/bin/bash

input_file="../../main"

input_args="../../input.txt"

# Output file to store the program's output
output_file="out.txt"

# Path to the expected output file for comparison
expected_output_file="../data/pos_$1_out.txt"

# Copy the contents of the input file for the test case
cp "../data/pos_$1_in.txt" "$input_args"

# Run the main executable with the provided input arguments
"$input_file" "$input_args" > "$output_file"

# Get the expectation and variance values from the output file
expectation=$(sed -n '1p' "$output_file")
variance=$(sed -n '2p' "$output_file")

# Get the expected expectation and variance values from the expected output file
expected_expectation=$(sed -n '1p' "$expected_output_file")
expected_variance=$(sed -n '2p' "$expected_output_file")

# Compare the actual and expected values
if [ "$expectation" = "$expected_expectation" ] && [ "$variance" = "$expected_variance" ]; then
    echo -e "POS_$1: \e[32mPASSED\e[0m"
else
    echo -e "POS_$1: \e[31mFAILED\e[0m"
    diff "$output_file" "$expected_output_file" >/dev/null  # Compare the output files and discard the diff output
fi

# Clean up by removing the output file and input arguments file
rm -f "$output_file" "$input_args"
