#!/bin/bash

../../main < "../data/pos_$1_in.txt" > "out.txt"
rc=$?

if ./comparator.sh out.txt ../data/pos_"$1"_out.txt; then
    echo -e POS_"$1": "\e[32mPASSED\e[0m"
else
    echo -e POS_"$1": "\e[31mFAILED\e[0m"
    ./comparator.sh out.txt ../data/pos_"$1"_out.txt
fi

#rm -f "out.txt"

