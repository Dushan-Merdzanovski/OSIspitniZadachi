#!/usr/bin/perl -w

$prva=$ARGV[0];
$vtora=$ARGV[1];
$izlez=$ARGV[2];
print "$prva $vtora";
open V1, $prva;
open V2, $vtora;
open IZL, ">$izlez";
open EKRAN,'>-';


@vlez1=<V1>;
@vlez2=<V2>;
$prva=@vlez1;
$vtora=@vlez2;

if ( $prva > $vtora ){
    for (@vlez2){
        print IZL $_,$vlez1[0];
        print EKRAN $_,$vlez1[0];
        shift(@vlez1);
    }
    print IZL @vlez1;
    print EKRAN @vlez1;
    }
else {
    for (@vlez1){
        print IZL $_,$vlez2[0];
        print EKRAN $_,$vlez2[0];
        shift(@vlez2);
    }
    print IZL @vlez2;
    print EKRAN @vlez2;
}


