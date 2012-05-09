#!/bin/sh

# Kernel iptables ipmasquerading/firewalling script.
echo "implementing firewall rules"

export EXT=eth0
export INT=eth1

# Flush all existing iptables rules.
iptables -F; iptables -t nat -F;iptables -t mangle -F

# Prepare iptables for NAT.
#iptables -t nat -A POSTROUTING -o ${EXT} -j MASQUERADE

# Allow forwarding of packets.
echo 1 > /proc/sys/net/ipv4/ip_forward

# Allow in ESTABLISHED and RELATED connections
iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT

# Allow NEW connections from everything except our external adapter
iptables -A INPUT -m state --state NEW ! -i ${EXT} -j ACCEPT

# Set default incoming policy to DROP
iptables -P INPUT DROP

#accept all from local network
iptables -A INPUT -s 192.168.0.0/24 -j ACCEPT
iptables -A INPUT -i lo -j ACCEPT

# allow SSH to this server
iptables -A INPUT -p tcp --syn --destination-port 22 -d 140.142.159.155 -j ACCEPT
iptables -A INPUT -p tcp --syn --destination-port 22 -d 192.168.0.100 -j  ACCEPT

# allow HTTP to this server
iptables -A INPUT -p tcp --syn --destination-port 80 -d 140.142.159.155 -j ACCEPT
iptables -A INPUT -p tcp --syn --destination-port 80 -d 192.168.0.100 -j ACCEPT

### Define incoming port forwards ###
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.207 -j DNAT --to-dest 192.168.0.101
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.200 -j DNAT --to-dest 192.168.0.102
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.202 -j DNAT --to-dest 192.168.0.103
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.205 -j DNAT --to-dest 192.168.0.104
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.203 -j DNAT --to-dest 192.168.0.105
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.175 -j DNAT --to-dest 192.168.0.106
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.204 -j DNAT --to-dest 192.168.0.107
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.177 -j DNAT --to-dest 192.168.0.108
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.178 -j DNAT --to-dest 192.168.0.109
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.179 -j DNAT --to-dest 192.168.0.110
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.180 -j DNAT --to-dest 192.168.0.111
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.181 -j DNAT --to-dest 192.168.0.112
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.182 -j DNAT --to-dest 192.168.0.113
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.183 -j DNAT --to-dest 192.168.0.114
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.184 -j DNAT --to-dest 192.168.0.115
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.185 -j DNAT --to-dest 192.168.0.116
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.186 -j DNAT --to-dest 192.168.0.117
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.187 -j DNAT --to-dest 192.168.0.118
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.188 -j DNAT --to-dest 192.168.0.119
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.189 -j DNAT --to-dest 192.168.0.120
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.190 -j DNAT --to-dest 192.168.0.121
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.191 -j DNAT --to-dest 192.168.0.122
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.192 -j DNAT --to-dest 192.168.0.123
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.193 -j DNAT --to-dest 192.168.0.124
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.194 -j DNAT --to-dest 192.168.0.125
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.206 -j DNAT --to-dest 192.168.0.126
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.196 -j DNAT --to-dest 192.168.0.127
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.197 -j DNAT --to-dest 192.168.0.128
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.198 -j DNAT --to-dest 192.168.0.129
iptables -t nat -A PREROUTING -i ${EXT}  -d 140.142.159.211 -j DNAT --to-dest 192.168.0.130

### Define our outgoing SNATS ###
iptables -t nat -A POSTROUTING -s 192.168.101 -j SNAT --to 140.142.159.207
iptables -t nat -A POSTROUTING -s 192.168.102 -j SNAT --to 140.142.159.200
iptables -t nat -A POSTROUTING -s 192.168.103 -j SNAT --to 140.142.159.202
iptables -t nat -A POSTROUTING -s 192.168.104 -j SNAT --to 140.142.159.205
iptables -t nat -A POSTROUTING -s 192.168.105 -j SNAT --to 140.142.159.203
iptables -t nat -A POSTROUTING -s 192.168.106 -j SNAT --to 140.142.159.175
iptables -t nat -A POSTROUTING -s 192.168.107 -j SNAT --to 140.142.159.204
iptables -t nat -A POSTROUTING -s 192.168.108 -j SNAT --to 140.142.159.177
iptables -t nat -A POSTROUTING -s 192.168.109 -j SNAT --to 140.142.159.178
iptables -t nat -A POSTROUTING -s 192.168.110 -j SNAT --to 140.142.159.179
iptables -t nat -A POSTROUTING -s 192.168.111 -j SNAT --to 140.142.159.180
iptables -t nat -A POSTROUTING -s 192.168.112 -j SNAT --to 140.142.159.181
iptables -t nat -A POSTROUTING -s 192.168.113 -j SNAT --to 140.142.159.182
iptables -t nat -A POSTROUTING -s 192.168.114 -j SNAT --to 140.142.159.183
iptables -t nat -A POSTROUTING -s 192.168.115 -j SNAT --to 140.142.159.184
iptables -t nat -A POSTROUTING -s 192.168.116 -j SNAT --to 140.142.159.185
iptables -t nat -A POSTROUTING -s 192.168.117 -j SNAT --to 140.142.159.186
iptables -t nat -A POSTROUTING -s 192.168.118 -j SNAT --to 140.142.159.187
iptables -t nat -A POSTROUTING -s 192.168.119 -j SNAT --to 140.142.159.188
iptables -t nat -A POSTROUTING -s 192.168.120 -j SNAT --to 140.142.159.189
iptables -t nat -A POSTROUTING -s 192.168.121 -j SNAT --to 140.142.159.190
iptables -t nat -A POSTROUTING -s 192.168.122 -j SNAT --to 140.142.159.191
iptables -t nat -A POSTROUTING -s 192.168.123 -j SNAT --to 140.142.159.192
iptables -t nat -A POSTROUTING -s 192.168.124 -j SNAT --to 140.142.159.193
iptables -t nat -A POSTROUTING -s 192.168.125 -j SNAT --to 140.142.159.194
iptables -t nat -A POSTROUTING -s 192.168.126 -j SNAT --to 140.142.159.206
iptables -t nat -A POSTROUTING -s 192.168.127 -j SNAT --to 140.142.159.196
iptables -t nat -A POSTROUTING -s 192.168.128 -j SNAT --to 140.142.159.197
iptables -t nat -A POSTROUTING -s 192.168.129 -j SNAT --to 140.142.159.198
iptables -t nat -A POSTROUTING -s 192.168.130 -j SNAT --to 140.142.159.211
