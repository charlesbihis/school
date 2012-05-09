#!/bin/sh
# Title: ping-test.sh
# Date: 02/07/2012
# Author: Charles Bihis
# Purpose: A script to test the DNS resolution of a my Q1 host 6 times.

if [ -f dns-script.log ];
	then
		rm dns-script.log;
fi

logdate=`date +"%Y-%m-%d-%H:%M:%S"`;

echo "Hostname: " `hostname` | tee -a dns-script.log > dns-script-`echo $logdate`.log;
ping -c 6 q2.ghost.ulcert.uw.edu | tee -a dns-script.log >> dns-script-`echo $logdate`.log;	# Note: host and ping-count is hardcoded here