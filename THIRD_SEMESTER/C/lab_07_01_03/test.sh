POSITIVES_SUCCEEDED=0
POSITIVES_MEMORY_SUCCEEDED=0
POSITIVES_SUM=0
NEGATIVES_SUCCEEDED=0
NEGATIVES_MEMORY_SUCCEEDED=0
NEGATIVES_SUM=0
POSITIVES_AMOUNT=17
NEGATIVES_AMOUNT=8

while [[ $POSITIVES_SUM -lt $POSITIVES_AMOUNT ]]
do
    ((POSITIVES_SUM++))
    index=`printf '%02d' $POSITIVES_SUM`
    args=`cat func_tests/pos_${index}_args.txt`
    if [ -s log/valg${index}_pos.txt ]
    then
        rm log/valg${index}_pos.txt
    fi

    if [[ "$1" == "-m" ]]
    then
        valgrind -q --log-fd=9 9>log/valg${index}_pos.txt --leak-check=full $args
    else
        $args
    fi

    exit_code=$?

    if [[ "$exit_code" == "0" && "`cat func_tests/test.txt`" == "`cat func_tests/pos_${index}_out.txt`" ]]
    then
        ((POSITIVES_SUCCEEDED++))

        rm func_tests/test.txt
        if [ -f log/pos$index.txt ]
        then
            rm log/pos$index.txt
        fi
    else
        if [[ "$exit_code" == "0" ]]
        then
            mv func_tests/test.txt func_tests/log/pos$index.txt
            echo -e "\e[31mFailed positive $index,\e[0m exit_code=$exit_code. See output in log/pos$index.txt"
        else
            echo -e "\e[31mFailed positive $index, exit_code=$exit_code.\e[0m"
        fi
    fi

    if [ -s log/valg${index}_pos.txt ]
    then
        echo -e "\e[1;33mMemory leak in positive $index.\e[0m Check valg${index}_pos.txt"
    else
        ((POSITIVES_MEMORY_SUCCEEDED++))
        
        if [[ $1 == "-m" ]]
        then
            rm log/valg${index}_pos.txt
        fi
    fi
done

while [[ $NEGATIVES_SUM -lt $NEGATIVES_AMOUNT ]]
do
    ((NEGATIVES_SUM++))

    index=`printf '%02d' $NEGATIVES_SUM`
    args=`cat func_tests/neg_${index}_args.txt`

    if [ -s log/valg${index}_neg.txt ]
    then
        rm log/valg${index}_neg.txt
    fi

    if [[ "$1" == "-m" ]]
    then
        valgrind -q --log-fd=9 9>log/valg${index}_neg.txt --leak-check=full $args
    else
        $args
    fi

    exit_code=$?

    if [[ "$exit_code" != "0" ]]
    then
        ((NEGATIVES_SUCCEEDED++))

        if [ -f log/neg$index.txt ]
        then
            rm log/neg$index.txt
        fi
    else
        mv func_tests/test.txt func_tests/log/neg$index.txt
        echo -e "\e[31mFailed negative $index,\e[0m exit_code=$exit_code. See output in log/neg$index.txt"
    fi

    if [ -s log/valg${index}_neg.txt ]
    then
        echo -e "\e[1;33mMemory leak in negative $index.\e[0m Check valg${index}_neg.txt"
    else
        ((NEGATIVES_MEMORY_SUCCEEDED++))
        if [[ $1 == "-m" ]]
        then
            rm log/valg${index}_neg.txt
        fi
    fi
done

echo -e "Succeeded positives $POSITIVES_SUCCEEDED/$POSITIVES_SUM (memory: $POSITIVES_MEMORY_SUCCEEDED/$POSITIVES_SUM)"

if [[ $POSITIVES_SUCCEEDED == $POSITIVES_SUM && $POSITIVES_MEMORY_SUCCEEDED == $POSITIVES_SUM ]]
then
    echo -e "\e[32mPOSITIVES PASSED\e[0m"
fi

echo "Succeeded negatives $NEGATIVES_SUCCEEDED/$NEGATIVES_SUM (memory: $NEGATIVES_MEMORY_SUCCEEDED/$NEGATIVES_SUM)"

if [[ $NEGATIVES_SUCCEEDED == $NEGATIVES_SUM && $NEGATIVES_MEMORY_SUCCEEDED == $NEGATIVES_SUM ]]
then
    echo -e "\e[32mNEGATIVES PASSED\e[0m"
fi
