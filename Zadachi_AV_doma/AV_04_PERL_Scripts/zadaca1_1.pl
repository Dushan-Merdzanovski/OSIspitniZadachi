#!/usr/bin/perl

@datoteki=@ARGV;
$kolku=@datoteki;

foreach (@ARGV) {
    open FH, $_;
    $prva_linija = <FH>;
    print $prva_linija;
}

$/='.';

foreach (@ARGV) {
    open FH, $_;
    $prva_linija = <FH>;
    print $prva_linija;
}
