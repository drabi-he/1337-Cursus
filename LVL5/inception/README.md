# INTRODUCTION

This document describes the process of setting up `inception`
It assume that you have a little experience with docker and docker-compose

# Basic Tips & Instructions

## 1. Run a basic Docker container in interactive mode

	docker run -it -p `[host_port]:[container_port]` `[image]:[tag]`

> :bulb: for this project, either `debian:buster` or `alpine:latest`

**FLAGS:**
  - `-i`: interactive mode (Keep STDIN open even if not attached)
  - `-t`: terminal mode (Allocate a pseudo-tty)
  - `-p`: port mapping

### 2. Try to setup the service from scratch

### 3. after you finish the setup successfully, create a Dockerfile

	FROM [image]:[tag]
	RUN [command]
	[...]
	COPY [source] [destination]
	[...]
	EXPOSE [port]
	CMD [command]


### 4. ADDITIONAL TIPS & INFORMATION

#### OpenRC

OpenRC is a system initialization framework that provides parallel startup of the various runlevels, starting and stopping of services and other system utilities in a sane and safe order.

**FLAGS:**
  - `mkdir -p ...` : create a directory and all parent directories if needed
  - `chown -R ...` : change the owner of a file or directory and all its subdirectories and files
  - `chmod 777 ...`: give read, write, and execute permissions to all users, including the owner, group, and others

---

# NGINX
<details>
<summary>Show/Hide</summary>

### 1. First update the package list

**debian:buster**

	apt update -y && apt upgrade -y

**alpine:latest**

	apk update && apk upgrade


### 2. Install NGINX and OpenSSL

**debian:buster**

	apt install -y nginx openssl

**alpine:latest**

	apk add nginx openssl

### 3. Create a self-signed certificate

	openssl req -x509 -new -newkey rsa:2048 -nodes -keyout /etc/ssl/private/localhost.key -out /etc/ssl/private/localhost.crt -subj "/C=MA/ST=Beni Mellal-Khenifra/L=Khouribga/O=42 Network/OU=IT/CN=localhost"

**FLAGS**
  - `req`: creates and processes certificate requests
  - `-x509`: generate a self-signed certificate
  - `-new`: create a new certificate request
  - `-newkey rsa:2048`: create a new private key using RSA and 2048 bit
  - `-nodes`: no passphrase/password (not encrypted)
  - `-keyout`: output the private key to a file
  - `-out`: generate the certificate to a file (*.crt/*.csr)
  - `-subj`: provide the certificate information
  	- `/C`: Country Name (2 letter code)
  	- `/ST`: State or Province Name (full name)
  	- `/L`: Locality Name (eg, city)
  	- `/O`: Organization Name (eg, company)
  	- `/OU`: Organizational Unit Name (eg, section)
  	- `/CN`: Common Name (eg, your name or your server's hostname)

> :bulb: for more detailed information about the `openssl req` command, check [this](https://www.openssl.org/docs/man1.1.1/man1/openssl-req.html)

### 4. Create a new NGINX configuration file

	vim /etc/nginx/nginx.conf
+ :arrow_right: [here](./alpine/srcs/requirements/nginx/conf/nginx.conf)

> **:warning: check if the configuration file is valid by running `nginx -t`**

### 5. Create the files you want to serve

	vim [path]/index.html
+ :arrow_right: [here](./alpine/srcs/requirements/nginx/tools/index.html)

> **:warning: the path is the same as the one you specified in the NGINX configuration file**

### 6. Start the NGINX service

**debian:buster**

	service nginx start

**alpine:latest**

	nginx

### 7. Test the service

from your host machine, open your browser and go to `https://localhost:[host_port]`

### 8. Additional Tips

**check if nginx compatible with TSLv1.2 and TLSv1.3**
  - for TSLv1.1 `should fail`

		curl -I -v --tlsv1.1 --tls-max 1.1 https://localhost:[host_port] -k

  - for TSLv1.2 `should pass if you have TLSv1.2`

		curl -I -v --tlsv1.2 --tls-max 1.2 https://localhost:[host_port] -k

  - for TSLv1.3 `should pass if you have TLSv1.3`

		curl -I -v --tlsv1.3 --tls-max 1.3 https://localhost:[host_port] -k

> :bulb: if you get `The plain HTTP request was sent to HTTPS port` try sending request to https instead of http

</details>

---

# MARIADB
<details>
<summary>Show/Hide</summary>

### 1. First update the package list

**debian:buster**

	apt update -y && apt upgrade -y

**alpine:latest**

	apk update && apk upgrade

### 2. Install MariaDB , MariaDB-client and OpenRC (for alpine)

> :bulb: since alpine can't run `service` command, we need to install `OpenRC` to be able to run `rc-service`

**debian:buster**

	apt install -y mariadb-server mariadb-client

**alpine:latest**

	apk add mariadb mariadb-client openrc

> :warning: since your system didn't boot with OpenRC, you will get an error when you try to start any service, to fix this, you need to run `openrc` and then `touch /run/openrc/softlevel`

	openrc && touch /run/openrc/softlevel

### 3. Create the directory where the `socket` file will be stored

	mkdir -p /var/run/mysqld

### 4. Change the owner of the directory to `mysql`

	chown -R mysql:mysql /var/run/mysqld

### 5. Change the permissions of the directory to avoid any complications

	chmod 777 /var/run/mysqld

### 6. Change in the configuration file

**debian:buster** `change the bind-address to allow connections from any IP`

	sed -i "s|bind-address            = 127.0.0.1|bind-address            = 0.0.0.0|g" /etc/mysql/mariadb.conf.d/50-server.cnf

**alpine:latest** `enable remote access`

	sed -i "s|skip-networking|skip-networking=0|g" /etc/my.cnf.d/mariadb-server.cnf

### 7. Run the `mysql_install_db` command to create the database

**debian:buster** `no option`

	mysql_install_db

**alpine:latest**

	mysql_install_db --user=mysql --datadir=/var/lib/mysql

### 8. Start the MariaDB service

**debian:buster**

	service mysql start

**alpine:latest**

	rc-service mariadb start

### 9. Secure the installation

> :bulb: you can use the `mysql_secure_installation` command to secure the installation, but it will ask you for a password, so you can use the following commands instead

**debian:buster**

	# Change the root password
	mysql -u root -e "UPDATE mysql.user SET Password=PASSWORD('ROOT_PASSWORD') WHERE User='root'; FLUSH PRIVILEGES;";

	# Remove anonymous users
	mysql -u root -pROOT_PASSWORD -e "DELETE FROM mysql.user WHERE User=''; FLUSH PRIVILEGES;";

	# Remove all root users except the localhost
	mysql -u root -pROOT_PASSWORD -e "DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1'); FLUSH PRIVILEGES;";

	# Remove all the test databases
	mysql -u root -pROOT_PASSWORD -e "DROP DATABASE IF EXISTS test; FLUSH PRIVILEGES;";
	mysql -u root -pROOT_PASSWORD -e "DELETE FROM mysql.db WHERE Db='test' OR Db='test\\_%'; FLUSH PRIVILEGES;";

	# Create a root user for remote access
	mysql -u root -pROOT_PASSWORD -e "CREATE USER 'root'@'%' IDENTIFIED BY 'ROOT_PASSWORD'; FLUSH PRIVILEGES;";

	# Grant all privileges to the remote root user
	mysql -u root -pROOT_PASSWORD -e "GRANT ALL ON *.* TO 'root'@'%' IDENTIFIED BY 'ROOT_PASSWORD'; FLUSH PRIVILEGES;";

	# Create a database and a user for remote access
	mysql -u root -pROOT_PASSWORD -e "CREATE DATABASE IF NOT EXISTS DB_NAME; GRANT ALL ON DB_NAME.* TO 'DB_USER'@'%' IDENTIFIED BY 'USER_PASSWORD'; FLUSH PRIVILEGES;"

**alpine:latest**

	# Change the root password
	mysql -u root -e "SET PASSWORD FOR 'root'@'localhost' = PASSWORD('ROOT_PASSWORD'); FLUSH PRIVILEGES;";

	# Remove anonymous users for localhost and other hosts
	mysql -u root -pROOT_PASSWORD -e "DROP USER ''@'localhost'; FLUSH PRIVILEGES;";
	mysql -u root -pROOT_PASSWORD -e "DROP USER ''@'$(hostname)'; FLUSH PRIVILEGES;";

	# Remove the test database
	mysql -u root -pROOT_PASSWORD -e "DROP DATABASE IF EXISTS test; FLUSH PRIVILEGES;";

	# Create a root user for remote access
	mysql -u root -pROOT_PASSWORD -e "CREATE USER 'root'@'%' IDENTIFIED BY 'ROOT_PASSWORD'; FLUSH PRIVILEGES;";

	# Grant all privileges to the remote root user
	mysql -u root -pROOT_PASSWORD -e "GRANT ALL ON *.* TO 'root'@'%' IDENTIFIED BY 'ROOT_PASSWORD'; FLUSH PRIVILEGES;";

	# Create a database and a user for remote access
	mysql -u root -pROOT_PASSWORD -e "CREATE DATABASE IF NOT EXISTS DB_NAME; GRANT ALL ON DB_NAME.* TO 'DB_USER'@'%' IDENTIFIED BY 'USER_PASSWORD'; FLUSH PRIVILEGES;";

**FLAGS:**
  - `-u .....` : connect to the MySQL server as the given username
  - `-pXXXX` : use the given password to authenticate the connection
  - `-e "..."` : execute the given command and quit

> :bulb: **use of environment variables is recommended**
> :bulb: for more information about the `mysql_secure_installation` command, you can check the [official documentation](https://mariadb.com/kb/en/mysql_secure_installation/)
> :bulb: for more information about automating `mysql_secure_installation`, you can check [this article](https://fedingo.com/how-to-automate-mysql_secure_installation-script/)
### 10. Stop the MariaDB service

**debian:buster**

	service mysql stop

**alpine:latest**

	rc-service mariadb stop

### 11. Run the `mysqld` command to start the service

	mysqld --user=mysql

### 12. Connect to the database from the host machine

	mysql -h 127.0.0.1 -P [HOST_PORT] -u [DB_USER / root] -p[USER_PASSWORD/ROOT_PASSWORD]

</details>