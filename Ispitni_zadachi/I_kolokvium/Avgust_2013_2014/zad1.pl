#!/usr/bin/perl -w

# 1. Да се напише perl скрипта за пресметување на потрошениот буџет на даден корисник,
# сметан според неговите сметки. Секоја сметка се чува во системот со екстензија .bill. Perl
# скриптата, како аргументи од командна линија добива листа од датотеки со екстензија „.bill“ и
# на екран печати извештај за потрошениот буџет. Форматот на секоја датотека е прикажан
# подолу. Во првата линија секогаш е запишан датумот на сметката, а во продолжение се
# запишани информации за купените продукти во формат: ime_produkt – tip_produkt – cena
# Скриптата треба на екран да отпечати за секој тип на продукт од сите сметки, колку е
# процентуално потрошено пари од буџетот, и на крај да се отпечати колку вкупно пари се
# потрошени од сите сметки.
# > primer.bill
# 21.08.2014
# Bounty – Cokolado – 23
# Snickers – Cokolado – 29
# Baduco – Riba – 35
# На екран:
# Cokolado – 59%
# Riba – 40 %
# Vkupno: 87 denari

%apole = ();
foreach $dat(@ARGV) {
    open DAT, $dat or die "Ne mozhe da se otvori $dat";
    $i = 0;
    while(<DAT>) {
        if ($i != 0) {
            $linija = $_;
            chomp $linija;
            ($prvz,$vtorz,$tretz) = split ' - ', $linija;
            if (exists($apole{$vtorz})) {
                    $apole{$vtorz} += $tretz;
            } else {
                $apole{$vtorz} = $tretz;
            }
        }
        $i++;
    }
    close DAT;
}

@klucevi = keys(%apole);
$vkupno = 0;
foreach $kluc(@klucevi) {
    # print "$kluc - $apole{$kluc}den\n";
    $vkupno += $apole{$kluc};
}


foreach $kluc(@klucevi) {
    $procent = $apole{$kluc}/$vkupno*100;
    printf("%s - %.2fprocenti \n", $kluc, $procent);
}

print "Vkupno: $vkupno denari\n";