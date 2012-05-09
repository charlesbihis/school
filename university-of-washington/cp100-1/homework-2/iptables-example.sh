#!/bin/bash

####
# Example firewall for University of Washington Unix Linux Administration
# Class Autumn 2011
####

echo "Executing Firewall Script"

#Lets define some variables so when we update our script we update variables instead of many lines of iptables commands
IPT=/sbin/iptables
EXT=eth0
#INT=eth1

#First lets flush all existing rules so when this is executed again it doesn't double up
$IPT -F

#We want a WhiteListing firewall so we're going to initially BLOCK all incoming packets
$IPT -P INPUT DROP

#Of course we want to connect to ourselves so lets allow the loopback device
$IPT -A INPUT -i lo -j ACCEPT

#We are blocking all incoming packets not from the lo device.  What about return packets from requests/outgoing packets we make/send?  lets allow those (established/related)
$IPT -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT

#
#We need to allow in The following Services for our server
#We allow SYN packets only because once we accept the SYN
#packet everything will then classify as an Established/Related
#connection and we don't have to worry about accepting random
#packets that aren't already associated with a valid connection

# This rule will flag any NEW SSH connections so we can see how many have come
# in from a given ip to our external interface
$IPT -I INPUT -p tcp --dport 22 -i $EXT -m state --state NEW -m recent --set

# This rule will drop any NEW SSH packets if more than 3 have come in
# the last 600 seconds.  This is our Rate Limiting rule
$IPT -I INPUT -p tcp --dport 22 -i $EXT -m state --state NEW -m recent --update --seconds 600 --hitcount 3 -j DROP


# Global Allow SSH from Anwhere AFTER our Rate limiting Rules
$IPT -A INPUT -p tcp --syn --dport 22 -j ACCEPT

#WWW
$IPT -A INPUT -p tcp -m state --state NEW -m multiport --dports 80,443 -j ACCEPT

#DNS
$IPT -A INPUT -p tcp --syn --dport 53 -j ACCEPT
$IPT -A INPUT -p udp --dport 53 -j ACCEPT

#MAIL/SMTP
$IPT -A INPUT -p tcp --syn --dport 25 -j ACCEPT

####
# Last INPUT rule - we're going to log it before we DROP it
####

$IPT -A INPUT -j LOG

####
# Above is our INCOMING protection rules.
# Below is our OUTGOING protection rules -
# For use on a restrictive machine - or possibly
# a desktop
####

#Lets drop all outoing packets by default.  We want to
#Restrict our users and potential malicious traffic leaving
#our server
$IPT -P OUTPUT DROP

#Lets allow our server to query DNS
$IPT -A OUTPUT -p tcp -o $EXT -d 140.142.159.151 --dport 53 -j ACCEPT
$IPT -A OUTPUT -p udp -o $EXT -d 140.142.159.152 --dport 53 -j ACCEPT
# or if we don't know our DNS servers for sure:
#$IPT -A OUTPUT -p tcp -o $EXT --dport 53 -j ACCEPT
#$IPT -A OUTPUT -p udp -o $EXT --dport 53 -j ACCEPT

#We're going to allow DHCP requests from our client
$IPT -A OUTPUT -p udp --dport 67:68 --sport 67:68 -j ACCEPT

#Lets allow outgoing SSH to the internet
$IPT -A OUTPUT -p tcp --dport 22 -j ACCEPT

#Open website browsing. The rule after is an example
#to force web traffic through a proxy
$IPT -A OUTPUT -p tcp -o $EXT --dport 80 -j ACCEPT
$IPT -A OUTPUT -p tcp -o $EXT --dport 443 -j ACCEPT
#EXAMPLE: Block _all_ web traffic unless they are going 
#through our proxy - 192.168.0.101
#$IPT -A OUTPUT -p tcp --dport 80 -d 192.168.0.101 -j ACCEPT
#$IPT -A OUTPUT -p tcp --dport 443 -d 192.168.0.101 -j ACCEPT

####
# Last OUTPUT rule - we're going to log it before we DROP it
####
$IPT -A OUTPUT -j LOG

####
# Below is a sample Syntax if you wanted to do NAT 
####

#Lets allow IP Masquerading out out EXT interface
#$IPT -t nat -A POSTROUTING -o $EXT -j MASQUERADE

#Must change a kernel parameter to allow the forwarding of packets
#echo 1 > /proc/sys/net/ipv4/ip_forward

#Example to forward port 80 to an internal server
# 192.168.0.80 that we are the gateway for
#$IPT -t NAT -A PREROUTING -i $INT -p tcp --dport 80 -j DNAT --to-dest 192.168.0.80
