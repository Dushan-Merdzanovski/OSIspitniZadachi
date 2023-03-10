#!/usr/bin/bash
# 2. Да се напише Shell скрипта која како аргументи од командна линија добива имиња на два директориуми,
# притоа доколку се повика без аргументи, скриптата испишува порака за грешка, додека пак, доколку се
# повика со еден аргумент, вториот се смета дека е тековниот директориум. Скриптата треба да ја земе првата
# текстуална датотека од двата директориуми (со екстензија .тхт) и да ја повика PERL скриптата, со тоа што
# како прв аргумент ќе се прати датотеката од првиот директориум, додека како втор аргумент датотеката од
# вториот директориум. Доколку двата директориуми се исти, тогаш вториот директориум се заменува со
# тековниот директориум. На крај да се отпечати резултатот од извршување на PERL скриптата.

if [ "$#" -eq 0 ]
then
    echo "Nedovolno vneseni argumenti"
    exit    
else
    dir1="$1"
    if [ "$#" -eq 1 ] # ako se samo 2 arg, vtoriot e PWD
    then 
        dir2="$PWD"        
    fi
    if [ "$#" -eq 2 ]
    then
        dir2="$2"
    fi
fi

if [ "$dir1" = "$dir2" ]
then
    dir2="$PWD"
fi

echo $dir1
echo $dir2

dat1=$(find ${dir1} -name "*.txt" | head -1)  # prviot fajl da go zeme
dat2=$(find ${dir2} -name "*.txt" | head -1)  # prviot fajl da go zeme

rez=$(./zadaca1.pl $dat1 $dat2)

echo $rez

