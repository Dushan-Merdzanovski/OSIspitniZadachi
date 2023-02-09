#!/usr/bin/perl

$n = @ARGV;
if ($n < 2) {
    die "premalku argumenti na cmd line";
}

@lista = @ARGV;
for ($i = 0; $i < ($n/2); $i++) {
    if($lista[$i] != $lista[$n-$i]) {
        $tmp = $lista[$i];
        $lista[$i] = $lista[$n-$i]; # ili so -1-$i
        $lista[$n-$i] = $tmp;
    }
}
print "@lista ";
