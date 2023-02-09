#!/usr/bin/perl -w
# zadaca 2 kolokviumski/ispitni prezentacija



# naredbi.txt i vlez.txt gi prakja so cmd line
$brarg=@ARGV;
%apole=(); #asocijativno pole

if($brarg<2) 
{
    die "nedovolno argumenti";
}

open FH,ARGV[0] or die "ne moze da se otvori prvata datoteka";

while(<FH>) {
    chomp $_; #za bez '\n' noviot red, moze i bez toa so cut, default e $_ 
    $apole($_)=1; # e random vrednost
}

$naredba = "";

open VLEZ, ARGV[1] or die "Ne moze da se otvori vtorata datoteka";

$linija=1;
while(<VLEZ>) {
    $linija = $_;
    @zborovi = split ' ',$linija;
    while(@zborovi) { # ne raboti ova
        $zbor = $_;
        if($apole($zbor)) { #dali e naredba, od apole glea
            print $naredba; #prva iter: prazen string pechati
            $naredba = $zbor; #cat ja zima kako prva naredba
        } else {
            $naredba = "$naredba $zbor"; # mozhe i vaka $naredba = $naredba, $zbor;
        }
    }
}
print $naredba;

