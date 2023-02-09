#!/usr/bin/perl -w

$argCount = @ARGV;

if($argCount != 1)
{
    die "Invalid number of arguments! $!\n";
}

open FILE, $ARGV[0] or die "Couldn't open the file!\n";
open OUT, ">$ARGV[0]_fix" or die "Couldn't open the file!\n";

foreach $line (<FILE>)
{
    @words = ();

    while($line =~ /\d+[a-zA-Z]+/g)
    {
        push(@words, $&);
    }

    $wordsNumber = @words;
    for(my $i = 0; $i < $wordsNumber; $i++)
    {
        @wordChars = split("", $words[$i]);

        if("$wordChars[0]" != "0")
        {
            if("$wordChars[0]" != "$i")
            {
                $pos = $wordChars[0];

                print "Swapping: $words[$i] $words[$pos-1] \n";
                ($words[$i], $words[$pos-1]) = ($words[$pos-1], $words[$i]);
            }
        }
    }

    print OUT "@words\n";

    print "@words\n";
}