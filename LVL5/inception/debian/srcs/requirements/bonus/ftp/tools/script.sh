#!/bin/sh
mkdir -p /var/run/vsftpd/empty
adduser --home /var/www ${FTP_USER}
echo ${FTP_USER}:${FTP_PASSWORD} | chpasswd
adduser ${FTP_USER} root
exec /usr/sbin/vsftpd /etc/vsftpd.conf
