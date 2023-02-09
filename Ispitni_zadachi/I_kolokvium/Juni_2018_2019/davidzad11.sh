#!/usr/bin/bash

lsFiles=$(ls *.pp)

if [ $# -gt 1 ] | [ $# -lt 1 ]
then
    echo "Invalid number of arguments!"
    exit
fi

if [ ${#1} != 9 ]
then
    echo "Invalid length of the number!"
    exit
fi

for file in $lsFiles
do
    res=$(perl zad1.pl $file) 

    if [[ $res = *" "* ]]
    then
        output=$(echo "$res" | grep $1)
        echo "$output"
    fi
done