#!/usr/bin/perl -w

# 1. ( поени) Да се напише PERL скрипта која како аргумент добива име на датотека. Во рамки на 
# датотеката има зборови составени од букви (одделени со празно место) кои формираат 
# реченица (завршува со точка и не се простира во повеќе редови). Зборовите во дадена реченица
# се испомешани, притоа пред секој збор има бројка која кажува кој по ред е зборот во 
# реченицата. Доколку пред некој збор има нула, тогаш тој е на точна позиција во реченицата. 
# Точните реченици се запишуваат во датотека со исто име како и влезната, со наставка „_fix“.

$broj = @ARGV;
if ($broj < 1) {
    die 'Nema dovolno argumenti';
}

$ime = $ARGV[0];
open VLEZ, $ARGV[0] or die 'Ne moze da se otvori vleznata datoteka';
@pole=();
@fixpole=();
while(<VLEZ>) {
    $linija = $_;
    chomp $linija;
    @pole = split ' ',$linija;
    @fixpole = @pole;
    $brelem = @pole;
    for ($i = 0; $i < $brelem; $i++) {
        @broj = split '\d+', $pole[$i];
        @zbor = split '\D+', $pole[$i];
        if ("$broj[0]" == "0") {
            $fixpole[$i] = $zbor[1];
        } else {
            $fixpole[$broj[0]-1] = $zbor[1];
        }
    }
    open IZ, ">${ime}_fix" or die 'Ne moze da se otvori izlezna datoteka';
    print IZ "@fixpole\n";
}