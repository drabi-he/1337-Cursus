#!/bin/sh
mysql_install_db --user=mysql --datadir=/var/lib/mysql
rc-service mariadb start
if [ ! -d "/var/lib/mysql/$MYSQL_DATABASE" ]
then
mysql -u root -e "SET PASSWORD FOR 'root'@'localhost' = PASSWORD('$MYSQL_ROOT_PASSWORD');"
mysql -u root -p$MYSQL_ROOT_PASSWORD -e "DROP USER ''@'localhost';"
mysql -u root -p$MYSQL_ROOT_PASSWORD -e "DROP USER ''@'$(hostname)';"
mysql -u root -p$MYSQL_ROOT_PASSWORD -e "DROP DATABASE IF EXISTS test;"
mysql -u root -p$MYSQL_ROOT_PASSWORD -e "CREATE DATABASE IF NOT EXISTS $MYSQL_DATABASE; GRANT ALL ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';"
mysql -u root -e "GRANT ALL PRIVILEGES ON *.* TO 'root'@'localhost' IDENTIFIED BY '' WITH GRANT OPTION;"
mysql -u root -p$MYSQL_ROOT_PASSWORD -e "FLUSH PRIVILEGES;"
fi
rc-service mariadb stop
exec mysqld --user=mysql
