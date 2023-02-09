#!/usr/bin/perl -w
# Ikolokvium 2021/2022

$broj = $ARGV[0];
shift @ARGV;

$kolku = @ARGV;
if($kolku - $broj <= 1) {
    die 'Nema dovolno izlezni datoteki';
}

@vlezni = @ARGV[0..($broj-1)];
@izlezni = @ARGV[$broj..($kolku-1)];
$/=" ";

foreach $izlez(@izlezni) {
    open IZ, ">$izlez" or die "Ne moze da se otvori izleznata dat: $izlez";
    print " izlezna dat:$izlez";
    print $bez = (split '\.', $izlez)[0];
    foreach $vl(@vlezni) {
        open VLEZ, $vl or die "Ne moze da se otvori vleznata dat: $vl";
        $kolku = 0;
        while ($zbor = <VLEZ>) {
            chomp $zbor;
            if($zbor eq $bez) {
                $kolku++;
            }
        }
        print IZ "$vl ima $kolku zborovi\n";
        close VLEZ;
    }
    close IZ;
}