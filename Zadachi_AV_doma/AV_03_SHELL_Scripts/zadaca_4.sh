#!/bin/bash
# ako ima pomalku od 3 argumenti na komandna linija se pechati help:
if [ $# -lt 3 ]
then
    echo "STOPPPPP"
    exit 0
fi
# ren – preimenuva poveke datoteki so pomosh na sed
# KORISTENJE: ren 'regizraz' 'zamena' datoteki...
# PRIMER: da se preimenuvaat site *.HTM datoteki vo *.html:
#ren 'HTM' 'html' *.HTM

OLD="$1"
NEW="$2"
# komandata shift otstranuva eden argument od listata 
shift
shift
# $* sega gi sodrzhi site datoteki:
for file in $*
do
    if [ -f "$file" ]
    then
        newfile=`echo "$file" | sed "s/${OLD}/${NEW}/g"`
        if [ -f "$newfile" ]
        then
            echo "ERROR: $newfile postoi"
        else
            echo "ja preimenuvam $file vo $newfile ..."
            mv "$file" "$newfile"
        fi
    fi
done