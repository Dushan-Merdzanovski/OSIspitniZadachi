#!/usr/bin/perl -w
#1.
#Да се напише ПЕРЛ скрипта која како аргументи од командна линија добива 2 датотеки (имиња на
#датотеки). Доколку има помалку од 2 датотеки, тогаш треба да се испише порака за грешка и да заврши
#скриптата. Првата датотека содржи парови зборови, по два зборови во секој ред посебно, втората
#датотека е датотека со случаен текст. Паровите зборови на првата датотека се граничници т.е. првиот
#збор е почетната граница а вториот збор е крајот. Скриптата треба да ги најде и отпечати сите зборови
#од втората датотека кои се наоѓаат од првиот граничен збор до вториот и да ги отпечати на екран. Ова
#треба да се направи за сите парови гранични зборови од првата датотека. Доколку некој од граничните
#зборови го нема во втората датотека или првиот не е пред вториот, во тој случај не се печати за тој пар
#гранични зборови ништо.
#Пример:
#Dat1.txt:
#prv vtor
#most koj
#tri kraj
#Dat2.txt
#Sekoj prv den sedime na most pokraj reka, I sekoj vtor od nas e koj od koj od elitata. Na kraj site se vratija na
#rabota
#На екран:
#prv den sedime na most pokraj reka, I sekoj vtor
#most pokraj reka, I sekoj vtor od nas e koj

$klk = @ARGV;

if ($klk < 2) {
    die "Nedovolno vneseni argumenti od cmd line";
}

open DAT1, $ARGV[0] or die "Ne moze da se otvori prvata datoteka";

%apole = ();
while (<DAT1>) {
    chomp $_;
    $linija = $_;
    ($prvzbor,$vtorzbor) = split ' ', $linija;
    $apole{$prvzbor}=$vtorzbor;
}

@klucevi=keys(%apole);
# foreach $kluc (@klucevi) {
#     print("$kluc $apole{$kluc} \n");
# }

open DAT2, $ARGV[1] or die "Ne moze da se otvori prvata datoteka";

@zborovi=();

while (<DAT2>) {
    chomp $_;
    $linija = $_;
    #@zborovi = split ' ',$linija;
    push @zborovi, (split ' ',$linija);
}

$broj=@zborovi;

$vorecenica=0;
$nasholdrug=0;
$j=0;
@finalna=();
foreach $k(@zborovi) {
    $vorecenica=0;
    $nasholdrug=0;
    $j++;
    foreach $kluc(@klucevi) {
        if ($k eq $kluc) {
            $vorecenica=1;
            for($i=$j; $i<$broj; $i++) {
                $finalna[$i-$j] = $zborovi[$i];
                if($zborovi[$i] eq $apole{$kluc}) {
                    $nasholdrug = 1;   
                    last;
                }
            }
            if($nasholdrug == 1) {
                print "$kluc @finalna";
                print "\n";
            }
        }
    }
}

