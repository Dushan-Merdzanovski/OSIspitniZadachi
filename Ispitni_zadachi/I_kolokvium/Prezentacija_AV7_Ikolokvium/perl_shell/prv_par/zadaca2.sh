#!/usr/bin/bash

dat1=$(find -name "naredbi1.txt")
dat2=$(find -name "vlez1.txt")

echo $dat1

if [ -z "$dat1" ]
then 
    echo "Ne postoi naredbi1.txt"
fi

if [ -z "$dat2" ]
then
    echo "Ne postoi vlez1.txt"
    exit
fi

$(cp $dat1 $PWD)
$(cp $dat2 $PWD)

rez=$(./zadaca1.pl naredbi1.txt vlez1.txt)

echo "$rez"

$(echo "" > izlez.txt)

for n in $rez # red po red gi zema
do
    $($n >> izlez.txt)
done