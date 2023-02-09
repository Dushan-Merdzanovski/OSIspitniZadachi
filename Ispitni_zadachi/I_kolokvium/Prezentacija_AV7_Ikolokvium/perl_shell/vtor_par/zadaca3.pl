#!/usr/bin/perl -w

$n = @ARGV;
$vlezna = $ARGV[0];
$izlezna = "${vlezna}_out";

open DAT1, $vlezna or die 'Ne moze da se otvori vleznata datoteka';
open DAT2, ">$izlezna" or die 'Nova datoteka izlezna ne moze da se otvori';


$bezdatumi="";
while(<DAT1>) {
    $linija = $_;
    chomp $linija;
    @datumi=();
    @zborovi=split ' ',$linija;
    foreach $zbor(@zborovi) {
        if($zbor =~ '[0][1-9]|[1-2][0-9]|3[0-1]\-[0][1-9]|1[0-2]\-[0-9][0-9][0-9][0-9]')
        {
            push (@datumi,$zbor);
        } else {
            $bezdatumi = "$bezdatumi $zbor"; # stringot sho kje go pechatime bez datumite
        }
    }
    $bezdatumi = "$bezdatumi\n";
    
    foreach $datum(@datumi) {
        print DAT2 "$datum $bezdatumi";
        if(($n == 2 ) && ($ARGV[1] eq "$datum") && ($ARGV[1] =~ '[0][1-9]|[1-2][0-9]|3[0-1]\-[0][1-9]|1[0-2]\-[0-9][0-9][0-9][0-9]'))
        {
            print "$datum $bezdatumi\n"
        }
    }
}

