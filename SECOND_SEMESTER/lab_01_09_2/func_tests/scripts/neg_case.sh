#!/bin/bash

../../main < "../data/neg_$1_in.txt" > "out.txt"
rc=$?

{
diff out.txt ../data/neg_"$1"_out.txt
rc_s=$?
} &> /dev/null

if [ $rc_s = 0 ] && [ $rc != 0 ]
then
    echo -e NEG_"$1": "\e[32mPASSED\e[0m"
else
    #echo "Error: Invalid input" > expected.txt
    #diff expected.txt ../data/neg_"$1"_out.txt
    echo -e NEG_"$1": "\e[31mFAILED\e[0m"
fi

rm -f "out.txt" "expected.txt"
