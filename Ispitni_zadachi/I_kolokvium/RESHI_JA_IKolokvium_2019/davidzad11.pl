#!/usr/bin/perl -w

# 1. Да се напише PERL скрипта која како аргументи од командна линија добива имиња на датотеки.
# Скриптата треба да ги измине датотеките и да провери колку различни валути на пари ќе најде. Знаците
# на валутите кои што се пребаруваат се: „$“ „€“ „£“ „kn“ „kr“ „Rp“ „CHF“. Секоја валута започнува со
# знакот на валутата, по кое што следи сумата на истата (одделена со празно место). Доколку после
# валутата нема бројка, тогаш валутата не се зема во предвид. Сите валути што ќе бидат пронајдени во
# датотеката се собираат и се добива вкупна сума по валута. За секоја валута што била пронајдена во
# датотеката, му се дозволува на корисникот да внесе колку денари е истата (не се внесува за оние валути
# кои што не биле пронајдени во тековната датотека). На крајот од изминувањето на датотеката да се
# отпечати вкупната сума (во денари) што била пронајдена во датотеката. Скриптата, на крај треба да
# отпечати кои валути биле пронајдени во сите датотеки. 

%currenciesCount = ();
foreach $file (@ARGV) {

    open FILE, $file or die "Couldn't open the file, $! \n";

    %currencies = ();
    %currenciesMkd = ();

    foreach $line (<FILE>) {
        while ($line =~ /(CHF|Rp|kr|kn|\$|£|€) \d+/g) {
            
            my ($currency, $value) = split(' ', $&);

            $currencies{$currency} += $value;
            $currenciesCount{$currency}++;
        }
    }

    open INPUT, '-';
    foreach my $curr (keys(%currencies)) {
        print "$curr, >MKD: ";

        $mkdValue = <INPUT>;
        $currenciesMkd{$curr} = $currencies{$curr} * $mkdValue;
    }

    print "$file: \n";
    foreach my $curr (keys(%currencies)) {
        print "$curr => $currencies{$curr} \n";
    }

    foreach my $curr (keys(%currenciesMkd)) {
        print "$curr => $currenciesMkd{$curr} MKD \n";
    }
}

foreach $currency (keys(%currenciesCount)) {
    print "$currency was found: $currenciesCount{$currency} times. \n";
}