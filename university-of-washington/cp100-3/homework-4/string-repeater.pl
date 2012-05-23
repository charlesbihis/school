#!/opt/csw/bin/perl
#
# Title: string-repeater.pl
# Author: Charles Bihis
# Date: 05/22/2012
# Purpose: A script that takes a string and a number and echoes the string the given number of times.


print "Hi!  Please enter a string: ";
chomp($string = <STDIN>);

print "Please enter how many times you would like this repeated: ";
chomp($repeatCount = <STDIN>);

print "You got it...\n\n";
while ($repeatCount > 0)
{
        print $string . "\n";
        $repeatCount--;
}
print "\nDone!\n";