#!/bin/sh

mysql_install_db --user=mysql --datadir=/var/lib/mysql

rc mariadb start

if [ -d "/var/lib/mysql/$MYSQL_DATABASE" ]
then
	echo "Database already exists"
else

mysql -u root -e "SET PASSWORD FOR 'root'@'localhost' = PASSWORD('$MYSQL_ROOT_PASSWORD'); FLUSH PRIVILEGES;"
mysql -u root -p$MYSQL_ROOT_PASSWORD -e "DROP USER ''@'localhost'; FLUSH PRIVILEGES;"
mysql -u root -p$MYSQL_ROOT_PASSWORD -e "DROP USER ''@'$(hostname)'; FLUSH PRIVILEGES;"
mysql -u root -p$MYSQL_ROOT_PASSWORD -e "DROP DATABASE IF EXISTS test; FLUSH PRIVILEGES;"

mysql -u root -p$MYSQL_ROOT_PASSWORD -e "CREATE USER 'root'@'%' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD'; FLUSH PRIVILEGES;"
mysql -u root -p$MYSQL_ROOT_PASSWORD -e "GRANT ALL ON *.* TO 'root'@'%' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD'; FLUSH PRIVILEGES;"
mysql -u root -p$MYSQL_ROOT_PASSWORD -e "CREATE DATABASE IF NOT EXISTS $MYSQL_DATABASE; GRANT ALL ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD'; FLUSH PRIVILEGES;"


mysql -u root -e "SET PASSWORD FOR 'root'@'localhost' = PASSWORD('1337'); FLUSH PRIVILEGES;"
mysql -u root -p1337 -e "DROP USER ''@'localhost'; FLUSH PRIVILEGES;"
mysql -u root -p1337 -e "DROP USER ''@'$(hostname)'; FLUSH PRIVILEGES;"
mysql -u root -p1337 -e "DROP DATABASE IF EXISTS test; FLUSH PRIVILEGES;"

mysql -u root -p1337 -e "CREATE USER 'root'@'%' IDENTIFIED BY '1337'; FLUSH PRIVILEGES;"
mysql -u root -p1337 -e "GRANT ALL ON *.* TO 'root'@'%' IDENTIFIED BY '1337'; FLUSH PRIVILEGES;"
mysql -u root -p1337 -e "CREATE DATABASE IF NOT EXISTS wordpress; GRANT ALL ON wordpress.* TO 'hdrabi'@'%' IDENTIFIED BY '4242'; FLUSH PRIVILEGES;"

fi
rc-service mariadb stop

exec mysqld --user=mysql