#!/opt/csw/bin/perl
#
# Title: date-and-time.pl
# Author: Charles Bihis
# Date: 05/22/2012
# Purpose: A script to print the date and time to the user

print "Hi!  What is your name?\n";
chomp($name = <STDIN>);
print "Good day, $name!  The date and time is " . localtime() . ".\n";