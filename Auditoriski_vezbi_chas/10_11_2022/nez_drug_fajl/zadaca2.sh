#!/usr/bin/fish

# OVAA RABOTI SO ZADACA1.PL 
#prvo dali ja ima vo tekovniot direktorium datotekata 

for dat in $@ # vo $@ site arg od cmd line se
do
    jaima=$(find . $dat)
    if [ -n $jaima ] # -n -> dali ne e prazna niza/string
    then
        x=$(sed 'p/[0-9][0-9]\-[0-9][0-9]\-[0-9][0-9][0-9][0-9]/') # print
        if [ -n $x ]
        then 
            $(./zadaca1.pl $dat)
            izlez="${dat}_out"
            kolku=$(wc -l $izlez)
            echo "$dat $kolku"
        fi
    fi
done