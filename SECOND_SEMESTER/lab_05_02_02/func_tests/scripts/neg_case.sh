#!/bin/bash

# Path to the main executable
input_file="../../main"

# Path to the input arguments file
input_args="../../input.txt"

# Copy the input from neg_$1_in.txt to input.txt
cp "../data/neg_$1_in.txt" "$input_args"

# Run the main executable with the updated input file
"$input_file" "$input_args" > "out.txt"
rc=$?

# Compare the output file with the expected output file
diff -q "out.txt" "../data/neg_$1_out.txt" &> /dev/null
diff_rc=$?

# Check if the output file matches the expected output file and the return code indicates success
if [ $diff_rc -eq 0 ] && [ $rc -ne 0 ]; then
    echo -e "NEG_$1: \e[32mPASSED\e[0m"  # Print a success message in green
else
    echo -e "NEG_$1: \e[31mFAILED\e[0m"  # Print a failure message in red
fi

# Clean up by removing the output file and input file
rm -f "out.txt" "$input_args"
