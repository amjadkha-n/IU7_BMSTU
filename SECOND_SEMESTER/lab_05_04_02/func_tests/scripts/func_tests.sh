#!/bin/bash

check_file_exists() {
    if [ ! -f "$1" ]; then
        echo "$2"
        exit 100
    fi
}

run_positive_tests() {
    if ! [ -f func_tests/data/pos_01_in.txt ]; then
        echo "No positive tests found."
    else
        for pos_test in func_tests/data/pos_??_in.txt; do
            number=$(echo "$pos_test" | grep -o '[0-9]\{2\}')
            cp "func_tests/data/pos_${number}_in_file.txt" "out_file.txt"
            cp "func_tests/data/pos_${number}_out_file.txt" "out_file_expect.txt"
            
            if ! [ -f "func_tests/data/pos_${number}_out.txt" ]; then
                echo "File data/pos_${number}_out.txt not found."
                tests_failed=$((tests_failed + 1))
            else
                ./app.exe t2b out_file.txt
                ./app.exe t2b out_file_expect.txt
                
                if ! func_tests/scripts/pos_case.sh "$pos_test" "func_tests/data/pos_${number}_out.txt" "func_tests/data/pos_${number}_args.txt" "out_file_expect.txt"; then
                    echo "pos_${number}_in.txt: failed."
                    tests_failed=$((tests_failed + 1))
                else
                    echo "pos_${number}_in.txt: passed."
                fi
                
                rm "out_file.txt"
                rm "out_file_expect.txt"
            fi
        done
    fi
}

run_negative_tests() {
    if ! [ -f func_tests/data/neg_01_in.txt ]; then
        echo "No negative tests found."
    else
        for neg_test in func_tests/data/neg_??_in.txt; do
            number=$(echo "$neg_test" | grep -o '[0-9]\{2\}')
            cp "func_tests/data/neg_${number}_in_file.txt" "out_file.txt"
            ./app.exe t2b out_file.txt
            
            if ! func_tests/scripts/neg_case.sh "$neg_test" "func_tests/data/neg_${number}_args.txt"; then
                echo "neg_${number}_in.txt: failed."
                tests_failed=$((tests_failed + 1))
            else
                echo "neg_${number}_in.txt: passed."
            fi
        done
    fi
}

check_file_exists "./app.exe" "Executable file not found."

tests_failed=0

run_positive_tests
run_negative_tests

if [ "$tests_failed" -eq 0 ]; then
    echo "All tests passed."
else
    echo "$tests_failed tests failed."
fi

exit $tests_failed

