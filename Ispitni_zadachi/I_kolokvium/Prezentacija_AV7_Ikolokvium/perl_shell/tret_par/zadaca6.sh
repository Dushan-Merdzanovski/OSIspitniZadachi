#!/usr/bin/bash

x=$1
rez=$(find . "files.txt");
if [ -z "$rez" ]
then
    echo "Files.txt ne e pronajdena"
    exit
fi

broj=$(wc -l < "files.txt")
if [ "$broj" -ge "$x" ] 
then 
    echo "X:${x} e pomal od Broj:${broj} datoteki"
    exit
fi

i=0;
datoteki=$(cat "files.txt")
y=$x
for dat in $datoteki
do 
    if [ -f $dat ] && [ $y -gt 0]
    then
        i=$(expr $i + 1)
    fi
    y=$(expr $y - 1)
done

if [ $i -neq $x ]
then 
    echo "Ne se site datoteki vo tekovniot direktorium"
    exit
fi
" \n"
$dva = 2
half=$(expr $x / $dva)
arg="-${x}"
prvi=$(head $arg $datoteki)
prvitex = $(sed -z 's/\n/ /g' files.txt)
$(./zadaca5.pl $half $prvitex)