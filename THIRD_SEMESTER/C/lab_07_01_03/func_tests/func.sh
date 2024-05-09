#!/bin/bash

echo "POSITIVE TESTS:"

for ((i = 1; i < 10; i++))
do
    num=$i
    if (( num < 10 ))
    then
        num="0$num"
    fi

    if [ -e "pos_${num}_in.txt" ] && [ -e "pos_${num}_out.txt" ] && [ -e "pos_${num}_args.txt" ]
    then
        sh positive_tests.sh $num
    else
        break
    fi
        done

echo " "
echo "NEGATIVE TESTS:"

for ((i = 1; i < 10; i++))
do
    num=$i
    if (( num < 10 ))
    then
        num="0$num"
    fi
    if [ -e "neg_${num}_in.txt" ] && [ -e "neg_00_out.txt" ] && [ -e "neg_${num}_args.txt" ]
    then
        sh negative_tests.sh $num
    else
        break
    fi
        done
