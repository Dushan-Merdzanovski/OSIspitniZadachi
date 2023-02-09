#!/usr/bin/bash

for dat in $@ 
do 
    jaima=$(find . -name "$dat")
    if [ -n "$jaima" ]
    then
        x=$(grep -o '[0-9][0-9]\-[0-9][0-9]\-[0-9][0-9][0-9][0-9]' "$dat") # USE THIS
        #x=$(grep -Po '\d\d\-\d\d\-\d\d\d\d' "$dat") mozhe i vaka
        if [ -n "$x" ]
        then
            $(./zadaca3.pl $dat)
            izlez="${dat}_out"
            kolku=$(wc -l $izlez)
            echo "$dat $kolku" 
        fi
    fi
done