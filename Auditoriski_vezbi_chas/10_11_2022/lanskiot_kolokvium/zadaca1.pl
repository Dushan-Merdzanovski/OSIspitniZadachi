#!/usr/bin/perl -w


$X = @ARGV[0];
shift @ARGV;
$kolku = @ARGV;
if ( $kolku <= $X ) {
    die "Nema dovolno izlezni datoteki"; # samo proverka e ova
}

# prvite $X datoteki se vlezni
@vlezni = @ARGV[0:$X-1];
@izlezni = @ARGV[$X:]; # $X: ide do kraj na nizata jako

$/=' '; # nov delimiter defaultniot go menja
while (@izlezni) {
    $izlezna = $_;
    open IZ,">$izlezna" or die "ne moze da se otvori izleznata datoteka $izlezna";
    while(@vlezni) {
        $bezekstenzija = (split ".",$_)[0]; # kje go splitne na 2 pr blabla.txt ke dae blabla i txt i samo blabla ni treba
        open VLEZ, $_ or die "Ne moze da se otvori vleznata datoteka"
        @zborovi = <VLEZ>;
        $kolku = 0;
        while(@zborovi) {
            if($_ == $bezekstenzija) {
                $kolku++;
            }
        }
        print IZ,"$_ ima $kolku zborovi";
        close VLEZ;
    }
}



