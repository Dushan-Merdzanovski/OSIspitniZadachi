#!/usr/bin/bash

# zaedno raboti zadaca1.pl

X=$1 #prv arg od cmd line

if [ -f "files.txt" ] # dali ja ima files.txt postoi blabla
then
#sekoj  
kolku=$(wc -l files.txt)
    if [ $X -le $kolku ] # gi izmenuva sekoj eden od niv
    then
        datoteki=$(cat files.txt)
        Y=$X # kolku dat prakjame na raspolaganje
        k=0
        for dat in $datoteki 
        do
            if [ -f $dat ] && [ $Y -gt 0] # za da gi proveri prvite Y datoteki
            then
                k=$(expr $k + 1) # ova e k++;
            fi
            Y=$(expr $Y - 1) # ova e Y--; koa ke doe do 0Y nema da gi proveruva ostanatite
        done
        if [ $k -eq $X ]  # site datoteki sho gi ima u datotekata, gi ima i vo tekovniot direktorium
        then
            # ako gi ima, ja povikuvame perl od prvata zadaca1.pl
            pola=$(expr $X \\ 2) # X/2
            arg="-${X}"
            prvi=$(head $arg $datoteki) #head gi zima prvite X datoteki/linii
            $(zadaca1.pl $pola $prvi)
        fi
    fi
fi