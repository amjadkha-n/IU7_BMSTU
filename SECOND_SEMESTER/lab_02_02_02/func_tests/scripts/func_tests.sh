#!/bin/bash

for ((i=1;i<100;i++))
do
    num=$(printf "%02d" $i)
    if [ -e "../data/pos_${num}_in.txt" ] && [ -e "../data/pos_${num}_out.txt" ]
    then
        ./pos_case.sh $num
    else
        break
    fi
done

echo

for ((i=1;i<100;i++))
do
    num=$(printf "%02d" $i)
    if [ -e "../data/neg_${num}_in.txt" ] && [ -e "../data/neg_${num}_out.txt" ]
    then
        ./neg_case.sh $num
    else
        break
    fi
done
