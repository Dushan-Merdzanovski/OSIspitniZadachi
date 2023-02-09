#!/usr/bin/perl

$n = @ARGV;

if($n < 3) {
    die "ima premalku datoteki na command line."
}
$dat1=$ARGV[0];
$dat2=$ARGV[1];
$dat3=$ARGV[2];

open FH1, $dat1;
open FH2, $dat2;
open FH3, ">$dat3";
open EKRAN, '>-';

# ne e dovrshena za ako brojot na linii ne e ist na datotekite
for (<FH1>) {
    $linija1 = $_;
    $linija2 = <FH2>;
    print FH3 $linija1, $linija2;
    print EKRAN $linija1, $linija2;
}



