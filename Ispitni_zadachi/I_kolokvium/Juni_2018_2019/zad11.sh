#!/usr/bin/bash

# Потоа, да се напише Shell скрипта која како аргумент од командна линија добива еден телефонски број
# (низа од 9 цифри која започнува со 07). Скриптата треба да ја повика Перл скриптата од претходно со
# секоја една датотека што ќе ја најде во тековниот директориум со екстензија „.рр“. Скриптата треба да
# провери за секоја една датотека дали воопшто го има телефонскиот број што го добива како аргумент и
# доколку го има, да го отпечати името на корисникот на тој телефонски број.

if [ $# != 1 ] 
then
    echo "Nema dovolno arguenti"
    exit
fi

telbroj=$1
string=$(ls *\.pp)

if [ -z $string ]
then 
    echo "Nema takvi datoteki vo $PWD"
    exit
fi

echo $string

i=0

for var in $string
do 
    res=$(./zad1.pl $var)
    if [[ $res = *" "* ]]
    then 
        output=$(echo "$res"|grep $telbroj)
        echo $output
    fi
done


# $(ls $PWD > "brojdatoteki.txt")
# brojdatoteki = $(cat "brojdatoteki.txt")

# for var in $string
# do 
#     check=$(grep -o "$telbroj" "$var")
#     if [ -n "$check" ]
#     then 
#         rez=$(./zad1.pl "${var}")
#         for zbor in $rez
#         do
#             check2=$(echo $zbor | grep "$telbroj")
# 			if [ -n "$check2" ]
# 			then
# 				echo "$zbor"
#             fi
#             # else 
#                 # echo "Check2 e prazna"
# 			# fi
#         done
#     else 
#         echo "Check e prazna."    
#     fi
# done