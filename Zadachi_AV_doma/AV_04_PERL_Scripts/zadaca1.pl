#!/usr/bin/perl -w

#@files = @ARGV;
$n = @ARGV;

$linija = 0;
#for(@ARGV) {
    for($i=0; $i < $n; $i++) {
        print $ARGV[$i]." ";
        open FH, $ARGV[$i] or print "Ne mozhe da se otvori";
        $linija = <FH>;
        print $linija;
    }
#}

$/='.';
for$i(@ARGV) {
    print $i." ";
    open FH, $i or print "Ne mozhe da se otvori";
    $linija = <FH>;
    print $linija,"\n";
    }

