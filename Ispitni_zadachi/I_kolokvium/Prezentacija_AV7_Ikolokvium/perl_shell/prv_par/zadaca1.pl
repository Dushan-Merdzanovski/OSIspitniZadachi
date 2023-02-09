#!/usr/bin/perl -w

$brarg = @ARGV;
%apole=();

if ( $brarg < 2 ) {
    die "Nedovolno argumenti od cmd line";
}

open DAT1, $ARGV[0] or die "Ne moze da se otvori prvata datoteka";


while(<DAT1>) {
    $line = $_;
    chomp $line;
    $apole{$line} = 1;
}

open DAT2, $ARGV[1] or die "Ne moze da se otvori vtorata datoteka";

$naredba="";
#$i=0;
while(<DAT2>) {
    $linija = $_;
    chomp $linija;
    #print "vlegov vo while dat2 so $linija";
    @zborovi = split ' ',$linija;
    foreach $zbor(@zborovi) {
        #print "Vlegov vo dat2 inner while so zbor $zbor";
        if($apole{$zbor}) {
            #if($i != 0 && $i != 1){
            #    print "\n";
            #}
            #$i++;
            print "$naredba\n";
            $naredba = $zbor;
        } else {
            $naredba = "$naredba $zbor";
        }
    }
}
print $naredba;

