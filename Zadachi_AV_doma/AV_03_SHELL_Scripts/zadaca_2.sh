#!/bin/bash
fruitlist="Apple Pear Tomato Peach Grape"
for fruit in $fruitlist
do
    if [ "$fruit" = "Apple" ] || [ "$fruit" = "Pear" ] || [ "$fruit" = "Grape" ]
    then
        echo "Mnozina: ${fruit}s"
    else
        echo "Mnozina: ${fruit}es"
    fi
done

case $1 in  
    "apple") echo "${1}s";;
    "pear") echo "${1}s" ;;
    "grape") echo "${1}s" ;;
    "tomato") echo "${1}es" ;;
    "peach") echo "${1}es" ;;
    *) echo "Invalid"
esac