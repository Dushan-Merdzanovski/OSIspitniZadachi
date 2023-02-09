#!/usr/bin/perl -w

$datoteka=$ARGV[0];
%imenik=();
@pole=();
open DAT, "$datoteka" or die "Ne mozam da ja otvoram datotekata!";
while(<DAT>)
{
	$linija=$_;
	@pole=split ' ', $linija;
	$i=0;
	for(@pole)
	{
		$zbor=$_;
		if(("$zbor"=~ /^\b07[0-9][0-9][0-9][0-9][0-9][0-9][0-9]\b$/)&&($i!=0))
		{
			$imenik{$zbor}=$pole[$i-1];
		}
		$i++;
	}
}
@klucevi=keys(%imenik);
$broj_clenovi=@klucevi;
for($j = 0; $j < $broj_clenovi; $j++)
{
	print "$klucevi[$j]->$imenik{$klucevi[$j]}\n";
}
