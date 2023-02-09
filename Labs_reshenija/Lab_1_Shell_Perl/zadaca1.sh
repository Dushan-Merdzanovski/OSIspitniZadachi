#!/usr/bin/bash

if [ "$#" -eq 1 ] 
then
    if [ -e "$1" ]
    then
        echo "Datotekata e pronajdena vo $PWD"
        cat $1
    else 
        echo "Datotekata ne e vo $PWD, iako e prateno neshto preku argv"
        if [ -e "naredbi.txt" ]  
        then
            echo "Datotekata e pronajdena vo $PWD"
            cat naredbi.txt
        else
            res=$(find ./ -name "naredbi.txt")
            if [ -n $res ]
            then 
                echo "Datotekata e pronajdena vo $res"
                cp $res $PWD
                cat "naredbi.txt"
            else
            echo "Datotekata ne e pronajdena nikade"
            fi  
        fi 
    fi
else
    if [ -e "naredbi.txt" ]  
    then
        echo "Datotekata e pronajdena vo $PWD"
        cat naredbi.txt
    else
        res=$(find ./ -name naredbi.txt)
        if [ -n $res ]
        then 
            echo "Datotekata e pronajdena vo $res"
            cp $res $PWD
            cat "naredbi.txt"
        else
        echo "Datotekata ne e pronajdena nikade"
        fi  
    fi
fi