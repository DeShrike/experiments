#!/usr/bin/perl
use strict;
use warnings;

# print("What is your name ?\n");
# my $name = <STDIN>;
# print("Hello $name\n");

my $a = 123;
my $b = "765";
my $c = $a + $b;

if ($c > 100)
{
  print("$c is greater than 100\n");
}
else
{
  print("$c is smaller than 100\n");
}

my $d;

if (not defined $d)
{
  print("not defined\n");
}

my $num1 = rand();
my $num2 = rand(100);
my $num3 = rand(3.14);
my $num4 = int(rand(100));

my $xx = add($num1, $num2);
print("xx = $xx\n");

print("Num1 = $num1\n");
print("Num2 = $num2\n");
print("Num3 = $num3\n");
print("Num4 = $num4\n");

my $i = 0;
my $r;
my $total = 0;
my $count = 1_000_000;

while ($i < $count)
{
  $r = int(rand(10000));
  $total = $total + $r;
  # print("$r ");
  $i = $i + 1;
}

my $avg = $total / $count;
print("\nAverage: $avg\n");

my @list1 = (2, 7, 29, 34, 67);
my @list2 = ("apple", "banana", "peach");

foreach my $fruit (@list2)
{
  print("$fruit ");
}

foreach my $i (0..$#list2)
{
  print("$i) $list2[$i]\n");
}

print("\n");

sub add {
  my ($x, $y) = @_;
  my $z = $x + $y;
  return $z;
}
