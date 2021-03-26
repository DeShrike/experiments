#!/usr/bin/perl
use strict;
use warnings;

my $i = 0;
my $ra;
my $total = 0;
my $count = 10_000_000;
my @counts = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

while ($i < $count)
{
	if ($i % 100_000 == 0)
	{
		my $p = $i / $count * 100;
		print("$i / $count ($p %)\n");
	}

	$ra = int(rand(100000));
	$ra = "$ra";

	foreach my $char (split //, $ra) {
		my $ichar = int($char);
		$counts[$ichar] = $counts[$ichar] + 1;
		$total = $total + 1;
	}

	$i = $i + 1;
}

foreach my $i (0..$#counts)
{
	my $perc = $counts[$i] / $total * 100;
	print("$i) $counts[$i] = $perc %\n");
}

print("\n");
