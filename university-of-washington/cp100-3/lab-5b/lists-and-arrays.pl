#!/opt/csw/bin/perl
#
# Title: lists-and-arrays.pl
# Author: Charles Bihis
# Date: 05/15/2012
# Purpose: A script to demonstrate common list and array actions in Perl.

# create array called "bread" that contains a list of ingredients
my @bread = ("yeast", "water", "salt", "flour");

# print the whole array
print "@bread\n";

# print only the 2nd and 4th elements
print $bread[1] . " " . $bread[3] . "\n";

# allow user to add new ingredient
chomp($newIngredient = <STDIN>);
push(@bread, $newIngredient);

# print array with new ingredient
print "@bread\n";

# remove the first item in the array using the shift() method
shift(@bread);

# print resulting array
print "@bread\n";

# print the last value of the array by referencing the index using the array size
print $bread[$#bread] . "\n";

# print all of the items in the array, but this time using a foreach loop
foreach (@bread)
{
	print $_ . " ";
}
print "\n";