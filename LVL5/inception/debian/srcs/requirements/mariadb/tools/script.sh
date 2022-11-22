#!/bin/sh

mysql_install_db

service mysql start

if [ -d "/var/lib/mysql/$MYSQL_DATABASE" ]
then
	echo "Database already exists"
else

mysql -u root -e "UPDATE mysql.user SET Password=PASSWORD('$MYSQL_ROOT_PASSWORD') WHERE User='root'; FLUSH PRIVILEGES;"
mysql -u root -p$MYSQL_ROOT_PASSWORD -e "DELETE FROM mysql.user WHERE User=''; FLUSH PRIVILEGES;"
mysql -u root -p$MYSQL_ROOT_PASSWORD -e "DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1'); FLUSH PRIVILEGES;"
mysql -u root -p$MYSQL_ROOT_PASSWORD -e "DROP DATABASE IF EXISTS test; FLUSH PRIVILEGES;"
mysql -u root -p$MYSQL_ROOT_PASSWORD -e "DELETE FROM mysql.db WHERE Db='test' OR Db='test\\_%'; FLUSH PRIVILEGES;"

mysql -u root -p$MYSQL_ROOT_PASSWORD -e "CREATE USER 'root'@'%' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD'; FLUSH PRIVILEGES;"
mysql -u root -p$MYSQL_ROOT_PASSWORD -e "GRANT ALL ON *.* TO 'root'@'%' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD'; FLUSH PRIVILEGES;"
mysql -u root -p$MYSQL_ROOT_PASSWORD -e "CREATE DATABASE IF NOT EXISTS $MYSQL_DATABASE; GRANT ALL ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD'; FLUSH PRIVILEGES;"

# mysql -u root -e "UPDATE mysql.user SET Password=PASSWORD('1337') WHERE User='root'; FLUSH PRIVILEGES;"
# mysql -u root -p1337 -e "DELETE FROM mysql.user WHERE User=''; FLUSH PRIVILEGES;"
# mysql -u root -p1337 -e "DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1'); FLUSH PRIVILEGES;"
# mysql -u root -p1337 -e "DROP DATABASE IF EXISTS test; FLUSH PRIVILEGES;"
# mysql -u root -p1337 -e "DELETE FROM mysql.db WHERE Db='test' OR Db='test\\_%'; FLUSH PRIVILEGES;"

# mysql -u root -p1337 -e "CREATE USER 'root'@'%' IDENTIFIED BY '1337'; FLUSH PRIVILEGES;"
# mysql -u root -p1337 -e "GRANT ALL ON *.* TO 'root'@'%' IDENTIFIED BY '1337'; FLUSH PRIVILEGES;"
# mysql -u root -p1337 -e "CREATE DATABASE IF NOT EXISTS wordpress; GRANT ALL ON test.* TO 'hdrabi'@'%' IDENTIFIED BY '4242'; FLUSH PRIVILEGES;"

fi
service mysql stop

exec mysqld --user=mysql