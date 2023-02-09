#!/bin/bash
# Da se priazat sodrzinite na poveke tekstualni datoteki
# KORISTENJE: ./prikazidat txtdat1 txtdat2 ...
# PRIMER: ./prikazidat /home/marijaef/*.txt

for datoteka in $@
do
    cat -n $datoteka
done

for datoteka in $@
do 
    if [ -r "$datoteka" ] # if readable file
    then 
        echo "=========$datoteka========="
        cat -n $datoteka
    else 
        echo "ERROR: non readable file $datoteka"
    fi
done
