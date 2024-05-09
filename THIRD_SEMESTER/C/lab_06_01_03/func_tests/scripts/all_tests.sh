#!/bin/bash                                                                                                                                                                                                \
                                                                                                                                                                                                            
for ((i=1;i<2;i++))
do
   num=$i
if (( num < 2 ))
then
   num="0$num"
fi
if [ -e "pos_${num}_in.txt" ] && [ -e "pos_${num}_out.txt" ] && [ -e "pos_${num}_args.txt" ]
then
    sh pos_test.sh $num
else
    break
fi
    done

echo

for ((i=1;i<7;i++))
do
    num=$i
    if (( num < 7 ))
    then
        num="0$num"
    fi
    if [ -e "neg_${num}_in.txt" ] && [ -e "neg_${num}_out.txt" ] && [ -e "neg_${num}_args.txt" ]
    then
        sh neg_test.sh $num
    else
        break
    fi
      	done
