#!/bin/bash

if [ $# -lt 3 ]
then
    echo "STOPPPPP"
    exit 0
fi

old="$1"
new="$2"

shift
shift

for dat in $*
do
    if [ -f "$dat" ]
    then
        newdat=`echo "$dat" | sed "s/${old}/${new}/g"`
        if [ -f "$newdat" ]
        then
            echo "ERROR: postoi ${newdat}"
        else
            echo "Renaming $dat to $newdat..."
            mv "$dat" "$newdat"
        fi
    fi
done
