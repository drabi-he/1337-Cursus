#!/bin/sh
adduser -h /var/www -D ${FTP_USER}
echo ${FTP_USER}:${FTP_PASSWORD} | chpasswd
adduser ${FTP_USER} root
exec /usr/sbin/vsftpd /etc/vsftpd/vsftpd.conf
