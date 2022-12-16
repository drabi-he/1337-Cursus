#!/bin/sh
mysql_install_db
service mariadb start
if [ ! -d "/var/lib/mysql/$MYSQL_DATABASE" ]
then
mysql -u root -e "DROP DATABASE IF EXISTS test;"
mysql -u root -e "CREATE DATABASE IF NOT EXISTS $MYSQL_DATABASE; GRANT ALL ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';"
mysql -u root -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';"
mysql -u root -e "FLUSH PRIVILEGES;"
fi
mysqladmin shutdown -p${MYSQL_ROOT_PASSWORD}
exec mysqld --user=mysql
