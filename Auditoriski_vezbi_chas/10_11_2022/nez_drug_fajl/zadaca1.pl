#!/usr/bin/perl -w
# OVAA E OD DRUGIOT FAJL
# ~ go sporeduva patternot 

$d = @ARGV; # kolku arg od cmd line
$vlezna = $ARGV[0];
$izlezna = "${vlezna}_out"; # so {} vrednosta na promenlivata ja chita
open DAT1,$vlezna;
open DAT2,$izlezna;


while(<DAT1>) { 
    $linija = $_; # mozhe i ovde chomp
    @zborovi = split ' ',$linija;
    @datumi=();
    $bezdatumi="";
    while(@zborovi) {
        $zbor=$_;
        if($zbor =~ '([0][1-9]|[1-2][0-9]|[3][0-1])\-([0][1-9]|[1][0-2])\-[1980-2050]')
         {
            push (@datumi,$zbor);
        }
        else {
            $bezdatumi = "$bezdatumi $zbor";
        }

    }#kraj na linija
    while(@datumi) {
        $datum=$_;
        print DAT2 "$datum $bezdatumi";
        if($d > 1 && $ARGV[1] ~= '([0][1-9]|[1-2][1-9]|[3][0-1])\-([0][1-9]|[1][0-2])\-[1980-2050]' && $datum==$ARGV[1]) # dali argumentot
            print "$datum $bezdatumi"
    }

}



