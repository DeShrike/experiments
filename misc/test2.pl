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

	$ra = int(rand(10000));
	my $r = $ra % 10;
	$counts[$r] = $counts[$r] + 1;
	$total = $total + $ra;
	$i = $i + 1;
}

my $avg = $total / $count;
print("\nAverage: $avg\n");

foreach my $i (0..$#counts)
{
	my $perc = $counts[$i] / $count * 100;
	print("$i) $counts[$i] = $perc %\n");
}

print("\n");
