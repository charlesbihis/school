#!/bin/sh
# Title: ping-test.sh
# Date: 02/14/2012
# Author: Charles Bihis
# Purpose: A script to test the DNS resolution of a given host a given number of times.

# set variables
scriptname=$0;
logdate=$(date +"%Y-%m-%d-%H:%M:%S");

# check parameters
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