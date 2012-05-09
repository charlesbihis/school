#!/bin/sh
# Title: iptables.sh
# Author: Charles Bihis
# Date: 11/15/2011
# Purpose: A script to set up iptables
# Notes: This configuration allows all access on ports 22 (SSH), 80 (HTTP), and 443 (HTTPS).
#		 A more desirable solution would allow only TCP SYN packets to port these ports instead
#		 and rely on the state module to make more intelligent decisions about whether or not
#		 to accept or reject.

sudo iptables -A INPUT –i lo –j ACCEPT																	# Accept on loopback port
sudo iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT									# Make our iptables connections stateful
sudo iptables -A INPUT -p tcp --dport ssh -j ACCEPT														# Allow SSH (TCP connection to port 22)
sudo iptables -A INPUT -p tcp --dport http -j ACCEPT													# Allow HTTP traffic (TCP connection to port 80)
sudo iptables -A INPUT -p tcp --dport https -j ACCEPT													# Allow HTTPS traffic (TCP connection to port 443)
sudo iptables –P INPUT DROP																				# Change default policy to now DROP all packets that don’t hit the above rules
sudo iptables –A INPUT –m limit --limit 5/min –j LOG --log-prefix “iptables dropped: “ --log-level 7	# Log all dropped packets
sudo /sbin/service iptables save																		# Save configuration to /etc/sysconfig/iptables