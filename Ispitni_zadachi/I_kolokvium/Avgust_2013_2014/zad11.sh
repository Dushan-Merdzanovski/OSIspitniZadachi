#!/usr/bin/bash

# Да се креира Shell скрипта која ќе врши статистика на буџетот на даден корисник. Скриптата
# може да се повика со неколку знаменца во произволен редослед. Доколку се повика со знаменце
# „-m“ во продолжение треба да се наведе за кој месец се прави статистиката и да се пронајдат
# сите датотеки со екстензија „.bill“ од тој месец и да се повика Perl скриптата, така што како
# аргументи ќе се пратат тие датотеки. Доколку не се наведе „-m“ знаменцето, тогаш се прави за
# сите месеци. Доколку скриптата се повика со знаменце „-d“ тогаш во продолжение се наведува
# директориумот од каде да се пребаруваат „.bill“ датотеките. Доколку не се наведе знаменце „-d“,
# тогаш се пребарува во домашниот (Home) директориум на корисникот. Доколку погрешно се
# наведат знаменцата, да се отпечати порака за грешка.
# Напомена: Одредувањето на месецот на датотеката се прави според датумот на модифицирање,
# додека пак пребарувањето на датотеките се прави само во конкретниот директориум (не и во
# неговите под-директориуми).



# if [ $1 = $flagm ]
# then

# elif [ $1 = $flagd]
# then
#     if [ -n $2 ]
#     then
#         res=$(find $2 -name -maxdepth 1 "*\.bill")
#     else 
#         res=$(find . -maxdepth 1 -name "*\.bill")
#     fi

    
# else 
# then
#     echo "Nevalidni flags! smenete nesho!\n"
#     exit
# fi

flagm=0
flagd=0
searchmonth=""
searchdir=""
count=0
broj=$#
while [ $count -lt $broj ] 
do 
    if [ $1 = "-m" ]
    then
        flagm=1
        shift
        if [ $1 = "-d"]
        then
            echo "Nepravilno koristenje na znamenca!"
            exit
        fi
        searchmonth=$0
    elif [ $1 = "-d" ]
    then
        flagd=1
        shift
        if [ -z $1 ]
        then 
            echo "Nepravilno koristenje na znamenca!"
            exit
        fi
        searchdir="$1"
    fi
    count = $(expr $count + 1) 
done

if [ $flagm = 0 ]
then 
    if [$flagd = 0 ]
    then
        searchdir="/home"
        # howmany=$(wc -l<find $searchdir -maxdepth 1 -name "*\.bill")
        res=$(find $searchdir -maxdepth 1 -name "*\.bill")
    else 
        res=$(find $searchdir -maxdepth 1 -name "*\.bill")
    fi
    $(./zad1.pl $res)
else # flagm = 1, ima searchmonth
    if [$flagd = 0 ]
    then
        searchdir="/home"
    fi
    cd $searchdir
    res=$(ls -l *.bill | grep "$searchmonth")
    res1=$(echo $res | grep -o "[a-z0-9]*.bill*")
    $(./zad1.pl $res1)
fi