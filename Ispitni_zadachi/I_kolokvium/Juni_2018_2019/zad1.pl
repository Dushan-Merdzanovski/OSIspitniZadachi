#!/usr/bin/perl -w

# 1.
# Да се напише Perl скрипта за работа со датотеки. Скриптата, како аргумент од командна линија добива
# име на една влезна датотека. Скриптата треба да ги најде сите телефонски броеви во датотеката и
# сопствениците на тие телефонски броеви. Секој телефонски збор е составен од 9 цифри, притоа
# започнува со 07. Скриптата треба да ги најде сите различни телефонски броеви и на крај да ги отпечати.
# Зборот пред секој телефонски број означува кој е корисникот на кој припаѓа тој телефонски број.
# Скриптата треба да го отпечати на екран името на сопственикот на телефонскиот број и самиот
# телефонски број. Доколку во датотеката истиот телефонски број се појавува со различни корисници,
# тогаш се печати само последниот корисник што ќе биде пронајден во датотеката за тој телефонски број.
# Секој збор од друг збор во датотеката е одделен со празно место.
#
# Потоа, да се напише Shell скрипта која како аргумент од командна линија добива еден телефонски број
# (низа од 9 цифри која започнува со 07). Скриптата треба да ја повика Перл скриптата од претходно со
# секоја една датотека што ќе ја најде во тековниот директориум со екстензија „.рр“. Скриптата треба да
# провери за секоја една датотека дали воопшто го има телефонскиот број што го добива како аргумент и
# доколку го има, да го отпечати името на корисникот на тој телефонски број.

$broj = @ARGV;
if($broj < 1) {
    die "Nema dovolno argumenti";
}

$datoteka = $ARGV[0];
open DAT, $datoteka or die "Ne moze da se otvori datotekata";

%apole = ();
@pole = ();

while (<DAT>) {
    $linija = $_;
    chomp $linija;
    @pole = split ' ',$linija;
    $i = 0;
    foreach $zbor(@pole) {
        if ($zbor =~ /07\d\d\d\d\d\d\d/ && ($i!=0)) {
            $apole{$zbor} = $pole[$i-1];
        }
        $i++;
    }
}

@klucevi = keys(%apole);
$brojiminja = @klucevi;
for ($i = 0; $i < $brojiminja; $i++) {
    print "$klucevi[$i] $apole{$klucevi[$i]}\n"
}
