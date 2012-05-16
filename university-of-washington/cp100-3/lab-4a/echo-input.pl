#!/usr/bin/perl
#
# Title: echo-input.pl
# Author: Charles Bihis
# Date: 05/08/2012
# Purpose: A script that takes a number from the user and echoes it.

print "Please enter a number and I'll repeat it!\n";
chomp($num = <STDIN>);
print "You entered the number $num!\n";