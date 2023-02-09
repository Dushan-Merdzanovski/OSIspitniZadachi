#!/bin/fish

# prvo ke gi bara naredbi.txt i vlez.txt vo sistemot, i ke gi copy vo tekoven direktorium
# find ~ -name "naredbi.txt" find vaka raboti, ja vrakja celata pateka
# ako ne najde nishto, vrakja prazen string

dat1=$(find . -name "naredbi.txt")
dat2=$(find . -name "vlez.txt")

if [ -z $dat1 ] #dali e prazen string
then
    echo "Ne postoi datotekata naredbi.txt"
fi

if [ -z $dat2 ]
then
    echo "Ne postoi datotekata vlez.txt"
fi

$(cp $dat1 $PWD)
$(cp $dat2 $PWD)

# sea ja povikuva perl skriptata, od zadaca 2.pl
# rezultatot od ovaa se printa vo izlez.txt

rez=$(./zadaca2.pl naredbi.txt vlez.txt)
# ako ne se iskopiraat u pwd istovo ova samo rez=$(zadaca2.pl $dat1 $dat2) 
$(echo "" > izlez.txt) # vaka ja kreira datotekata

for n in $rez
do
    $($n >> izlez.txt)
done

