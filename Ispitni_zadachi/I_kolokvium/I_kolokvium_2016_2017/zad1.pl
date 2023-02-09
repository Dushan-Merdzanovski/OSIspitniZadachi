#!/usr/bin/perl -w
# 1.
# Да се напише PERL скрипта која како аргументи од командна линија добива листа од кориснички
# имиња. Секое корисничко име започнува со специјалниот знак „@“ а потоа следи листа од букви и
# бројки. Невалидните имиња од командна линија да се игнорираат. Скриптата дозволува да бидат
# внесени непознат број на имиња на датотеки од тастатура (прекинува кога ќе се внесе зборот „kraj“).
# Скриптата прави статистика за секоја една датотека, притоа статистиката вклучува секое едно
# корисничко име, во која линија од датотеката се појавува. Скриптата на екран ги печати (во секој ред
# одделно) во кој ред било пронајдено корисничкото име (бројот на редот) и кои други кориснички имиња
# биле пронајдени во истиот ред.
$brojarg = @ARGV;
@pole=();
for $zbor(@ARGV) {
    if($zbor =~ '@[a-zA-Z0-9]+') {
        push (@validni, $zbor);
    }
}
$inputword="";
@vneseni=();
print "\nVnesuvaj zborovi, kraj to quit\n";
do {
    chomp($inputword = <STDIN>);
    push (@vneseni, $inputword);
} while ($inputword ne "kraj");
pop(@vneseni);
for $dat(@vneseni) {
    $numline=1;
    open DAT, $dat or die "Ne moze da se otvori datotekata";
    print "\n\nVo dadotekata $dat:\n";
    while(<DAT>) {
        $linija = $_;
        chomp $linija;
        @linii = split ' ',$linija;
        $imavolinija = 0;
        @najdeni=();
        for $username(@validni) {
            for $iter(@linii) {
                if ($username eq $iter) {
                    $imavolinija=1;
                    push(@najdeni,$username);
                }
            }
        }
        if ($imavolinija) {
            print "\nVo linija $numline gi ima:\n";
            print "@najdeni";
        }
        $numline++;
    }
}