#!/usr/bin/perl -w

open DAT, "$ARGV[0]" or die "Ne mozam da ja otvoram datotekata!\n";
while(<DAT>)
{
	$linija=$_;
	@pole=split ' ', $linija;
	$kolku=@pole;
	$indeks=0;
	%broj_zbor=();
	for($j=0;$j<$kolku;$j++)
	{
		@zbor=split '\D+', $pole[$j];
		@broj=split '\d+', $pole[$j];
		if($broj[0] == 0)
		{
			$broj_zbor{$indeks}=$zbor[1];
		}
		else
		{
			$broj_zbor{$broj[0]}=$zbor[1];
		}
		$indeks++;
	}
	@klucevi=keys(%broj_zbor);
	$broj_klucevi=@klucevi;
	$s="";
	for($i=1;$i<=$broj_klucevi;$i++)
	{
		$s="$s $broj_zbor{$i}";
	}
	open IZLEZ, ">${ARGV[0]}_fix" or die "Ne mozam da ja otvoram datotekata za zapisuvanje!\n";
	print IZLEZ "$s\n";
}