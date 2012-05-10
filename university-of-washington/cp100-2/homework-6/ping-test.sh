#!/bin/sh
# Title: ping-test.sh
# Date: 02/21/2012
# Author: Charles Bihis
# Purpose: A script to test the DNS resolution of a given host a given number of times,
#		   with an added option for a help message.

# set variables
scriptname=$0;
logdate=$(date +"%Y-%m-%d-%H:%M:%S");

# check parameters
if [ $# == 1 -a $1 == "-h" ]
	then
		echo -e "\nThis is a script to test the DNS resolution of a given host a given number of times.  It's usage is:\n\n" $0 "[hostname] [ping-count]\n\n[hostname] is the fully-qualified domain name of the host you would like to test, and [ping-count] is the number of pings you would like to send.\n";
		exit 0;
fi

if [ $# != 2 ];
	then
		echo "Usage: " $0 "[hostname] [ping-count]";
		exit -1;
	else
		hostname=$1;
		pingcount=$2;
fi

# remove log file if it already exists
if [ -f $0.log ];
	then
		rm $0.log;
fi

# echo the hostname
echo "Hostname: " `hostname` | tee -a $0.log > $0-`echo $logdate`.log;

# perform the ping
ping -c $pingcount $hostname | tee -a $0.log >> $0-`echo $logdate`.log;