#!/bin/sh

echo "create inception directories ? (y/n)"

read answer

if [ "$answer" = "y"  ] || [ "$answer" = "Y"  ]
then

	# create the project directories and files
	mkdir inception
	touch inception/Makefile
	mkdir inception/srcs
	touch inception/srcs/.env
	touch inception/srcs/docker-compose.yml
	mkdir inception/srcs/requirements
	mkdir inception/srcs/requirements/tools
	mkdir inception/srcs/requirements/mariadb
	touch inception/srcs/requirements/mariadb/.dockerignore
	touch inception/srcs/requirements/mariadb/Dockerfile
	mkdir inception/srcs/requirements/mariadb/conf
	touch inception/srcs/requirements/mariadb/conf/docker.cnf
	mkdir inception/srcs/requirements/mariadb/tools
	touch inception/srcs/requirements/mariadb/tools/script.sh
	mkdir inception/srcs/requirements/nginx
	touch inception/srcs/requirements/nginx/.dockerignore
	touch inception/srcs/requirements/nginx/Dockerfile
	mkdir inception/srcs/requirements/nginx/tools
	touch inception/srcs/requirements/nginx/tools/.gitkeep
	mkdir inception/srcs/requirements/nginx/conf
	touch inception/srcs/requirements/nginx/conf/nginx.conf
	mkdir inception/srcs/requirements/wordpress
	touch inception/srcs/requirements/wordpress/.dockerignore
	touch inception/srcs/requirements/wordpress/Dockerfile
	mkdir inception/srcs/requirements/wordpress/conf
	touch inception/srcs/requirements/wordpress/conf/.gitkeep
	mkdir inception/srcs/requirements/wordpress/tools
	touch inception/srcs/requirements/wordpress/tools/script.sh
	mkdir inception/srcs/requirements/bonus
	mkdir inception/srcs/requirements/bonus/redis
	touch inception/srcs/requirements/bonus/redis/.dockerignore
	touch inception/srcs/requirements/bonus/redis/Dockerfile
	mkdir inception/srcs/requirements/bonus/redis/conf
	touch inception/srcs/requirements/bonus/redis/conf/.gitkeep
	mkdir inception/srcs/requirements/bonus/redis/tools
	touch inception/srcs/requirements/bonus/redis/tools/.gitkeep
	mkdir inception/srcs/requirements/bonus/ftp
	touch inception/srcs/requirements/bonus/ftp/.dockerignore
	touch inception/srcs/requirements/bonus/ftp/Dockerfile
	mkdir inception/srcs/requirements/bonus/ftp/conf
	touch inception/srcs/requirements/bonus/ftp/conf/vsftpd.conf
	mkdir inception/srcs/requirements/bonus/ftp/tools
	touch inception/srcs/requirements/bonus/ftp/tools/script.sh
	mkdir inception/srcs/requirements/bonus/website
	touch inception/srcs/requirements/bonus/website/.dockerignore
	touch inception/srcs/requirements/bonus/website/Dockerfile
	mkdir inception/srcs/requirements/bonus/website/conf
	mkdir inception/srcs/requirements/bonus/website/tools
	mkdir inception/srcs/requirements/bonus/adminer
	touch inception/srcs/requirements/bonus/adminer/.dockerignore
	touch inception/srcs/requirements/bonus/adminer/Dockerfile
	mkdir inception/srcs/requirements/bonus/adminer/conf
	touch inception/srcs/requirements/bonus/adminer/conf/.gitkeep
	mkdir inception/srcs/requirements/bonus/adminer/tools
	touch inception/srcs/requirements/bonus/adminer/tools/.gitkeep
	mkdir inception/srcs/requirements/bonus/portainer
	touch inception/srcs/requirements/bonus/portainer/.dockerignore
	touch inception/srcs/requirements/bonus/portainer/Dockerfile
	mkdir inception/srcs/requirements/bonus/portainer/conf
	touch inception/srcs/requirements/bonus/portainer/conf/.gitkeep
	mkdir inception/srcs/requirements/bonus/portainer/tools
	touch inception/srcs/requirements/bonus/portainer/tools/.gitkeep

	_CertName="self-signed"
	_DB_NAME="wordpress"
	_DB_USER="wpuser"
	_DB_PASS="wppass"
	_DB_ROOT_PASS="rootpass"
	_DOMAIN_NAME="localhost"
	_FTP_USER="ftpuser"
	_FTP_PASS="ftppass"

	echo "Setup environement variables"
	echo "self-signed certificate name : default ($_CertName)"

	read _CertName

	if [ "$_CertName" = "" ]
	then
		_CertName="self-signed"
	fi

	echo "Database name : default ($_DB_NAME)"

	read _DB_NAME

	if [ "$_DB_NAME" = "" ]
	then
		_DB_NAME="wordpress"
	fi

	echo "Database user : default ($_DB_USER)"

	read _DB_USER

	if [ "$_DB_USER" = "" ]
	then
		_DB_USER="wpuser"
	fi

	echo "Database password : default ($_DB_PASS)"

	read _DB_PASS

	if [ "$_DB_PASS" = "" ]
	then
		_DB_PASS="wppass"
	fi

	echo "Database root password : default ($_DB_ROOT_PASS)"

	read _DB_ROOT_PASS

	if [ "$_DB_ROOT_PASS" = "" ]
	then
		_DB_ROOT_PASS="rootpass"
	fi

	echo "Domain name : default ($_DOMAIN_NAME)"

	read _DOMAIN_NAME

	if [ "$_DOMAIN_NAME" = "" ]
	then
		_DOMAIN_NAME="localhost"
	fi

	echo "FTP user : default ($_FTP_USER)"

	read _FTP_USER

	if [ "$_FTP_USER" = "" ]
	then
		_FTP_USER="ftpuser"
	fi

	echo "FTP password : default ($_FTP_PASS)"

	read _FTP_PASS

	if [ "$_FTP_PASS" = "" ]
	then
		_FTP_PASS="ftppass"
	fi

	# Setup environment variables and .dockerignore
	echo "DOMAIN_NAME=$_DOMAIN_NAME" > inception/srcs/.env
	echo "_CERT=./requirements/tools/$_CertName.crt" >> inception/srcs/.env
	echo "_KEY=./requirements/tools/$_CertName.key" >> inception/srcs/.env
	echo "MYSQL_DATABASE=$_DB_NAME" >> inception/srcs/.env
	echo "MYSQL_ROOT_PASSWORD=$_DB_ROOT_PASS" >> inception/srcs/.env
	echo "MYSQL_USER=$_DB_USER" >> inception/srcs/.env
	echo "MYSQL_PASSWORD=$_DB_PASS" >> inception/srcs/.env
	echo "FTP_USER=$_FTP_USER" >> inception/srcs/.env
	echo "FTP_PASSWORD=$_FTP_PASS" >> inception/srcs/.env
	echo ".env" > inception/srcs/requirements/mariadb/.dockerignore
	echo ".git" >> inception/srcs/requirements/mariadb/.dockerignore
	echo ".env" > inception/srcs/requirements/nginx/.dockerignore
	echo ".git" >> inception/srcs/requirements/nginx/.dockerignore
	echo ".env" > inception/srcs/requirements/wordpress/.dockerignore
	echo ".git" >> inception/srcs/requirements/wordpress/.dockerignore
	echo ".env" > inception/srcs/requirements/bonus/redis/.dockerignore
	echo ".git" >> inception/srcs/requirements/bonus/redis/.dockerignore
	echo ".env" > inception/srcs/requirements/bonus/ftp/.dockerignore
	echo ".git" >> inception/srcs/requirements/bonus/ftp/.dockerignore
	echo ".env" > inception/srcs/requirements/bonus/website/.dockerignore
	echo ".git" >> inception/srcs/requirements/bonus/website/.dockerignore
	echo ".env" > inception/srcs/requirements/bonus/adminer/.dockerignore
	echo ".git" >> inception/srcs/requirements/bonus/adminer/.dockerignore


	# Setup Certificates
	sudo apt update -y && sudo apt upgrade -y
	sudo apt install -y curl docker docker-compose make wget libnss3-tools
	wget https://github.com/FiloSottile/mkcert/releases/download/v1.4.4/mkcert-v1.4.4-linux-amd64
	mv mkcert-v*-linux-amd64 mkcert
	chmod a+x mkcert
	sudo mv mkcert /usr/local/bin/
	cd inception/srcs/requirements/tools
	mkcert $_CertName
	mv $_CertName-key.pem $_CertName.key
	mv $_CertName.pem $_CertName.crt
	cd ../..

	# Directory script.sh
	{ echo '#!/bin/sh' ;
	echo 'mkdir -p ~/data' ;
	echo 'mkdir -p ~/data/mariadb' ;
	echo 'mkdir -p ~/data/wordpress' ;
	echo 'mkdir -p ~/data/portainer' ;
	} > ./requirements/tools/script.sh

	chmod +x ./requirements/tools/script.sh

fi



echo "Setup inception mandatory ? (y/n)"

read answer

if [ "$answer" = "y"  ] || [ "$answer" = "Y"  ]
then

	# Setup NGINX

	{ echo "FROM debian:stable" ;
	echo "RUN apt update -y && apt upgrade -y" ;
	echo "RUN apt install -y nginx" ;
	echo "EXPOSE 443" ;
	echo 'CMD ["nginx", "-g", "daemon off;"]' ; } > ./requirements/nginx/Dockerfile

	{ echo "server {" ;
	echo "	listen 443 ssl;" ;
	echo "	server_name $_DOMAIN_NAME www.$_DOMAIN_NAME;" ;
	echo "	ssl_certificate /etc/nginx/ssl/$_CertName.crt;" ;
	echo "	ssl_certificate_key /etc/nginx/ssl/$_CertName.key;" ;
	echo "	ssl_protocols TLSv1.2 TLSv1.3;" ;
	echo "	root /var/www/;";
	echo "	index index.php index.html;" ;
	echo "	location / {" ;
	echo '		try_files $uri /index.php?$args;' ;
	echo '		add_header Last-Modified $date_gmt;' ;
	echo "		add_header Cache-Control 'no-store, no-cache';" ;
	echo "		if_modified_since off;" ;
	echo "		expires off;" ;
	echo "		etag off;" ;
	echo "	}" ;
	echo "	location ~ \.php$ {";
	echo "		fastcgi_split_path_info ^(.+\.php)(/.+)$;";
	echo "		fastcgi_pass wordpress:9000;";
	echo "		fastcgi_index index.php;";
	echo "		include fastcgi_params;";
	echo '		fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;';
	echo '		fastcgi_param PATH_INFO $fastcgi_path_info;';
	echo "	}";
	echo "}"; } > ./requirements/nginx/conf/nginx.conf

	# Setup MariaDB

	{ echo "FROM debian:stable" ;
	echo "RUN apt update -y && apt upgrade -y" ;
	echo "RUN apt install -y mariadb-server mariadb-client" ;
	echo "RUN mkdir -p /var/run/mysqld && chown -R mysql /var/run/mysqld && chmod -R 777 /var/run/mysqld" ;
	echo 'RUN  sed -i "s|bind-address            = 127.0.0.1|bind-address            = 0.0.0.0|g" /etc/mysql/mariadb.conf.d/50-server.cnf' ;
	echo "COPY ./tools/script.sh ." ;
	echo "RUN chmod +x script.sh" ;
	echo 'CMD ["sh", "script.sh"]' ; } > ./requirements/mariadb/Dockerfile

	{ echo "#!/bin/sh" ;
	echo "mysql_install_db" ;
	echo "service mariadb start" ;
	echo 'if [ ! -d "/var/lib/mysql/$MYSQL_DATABASE" ]' ;
	echo "then" ;
	echo 'mysql -u root -e "DROP DATABASE IF EXISTS test;"' ;
	echo 'mysql -u root -e "CREATE DATABASE IF NOT EXISTS $MYSQL_DATABASE; GRANT ALL ON $MYSQL_DATABASE.* TO '"'"'$MYSQL_USER'"'@'%' IDENTIFIED BY '"'$MYSQL_PASSWORD'"'"';"' ;
	echo 'mysql -u root -e "ALTER USER '"'root'@'localhost' IDENTIFIED BY '"'${MYSQL_ROOT_PASSWORD}'"'"';"' ;
	echo 'mysql -u root -e "FLUSH PRIVILEGES;"' ;
	echo "fi" ;
	echo 'mysqladmin shutdown -p${MYSQL_ROOT_PASSWORD}'
	echo "exec mysqld --user=mysql" ; } > ./requirements/mariadb/tools/script.sh

	# Setup Wordpress

	{ echo "FROM debian:stable" ;
	echo "ARG MYSQL_DATABASE MYSQL_USER MYSQL_PASSWORD VERSION=7.4" ;
	echo "WORKDIR /var/www" ;
	echo "RUN apt update -y && apt upgrade -y" ;
	echo 'RUN apt install -y php${VERSION} php${VERSION}-fpm php${VERSION}-mysqli php${VERSION}-json php${VERSION}-curl php${VERSION}-dom php${VERSION}-exif php${VERSION}-fileinfo php${VERSION}-mbstring php${VERSION}-xml php${VERSION}-zip php${VERSION}-redis wget unzip' ;
	echo 'RUN sed -i "s|listen = /run/php/php${VERSION}-fpm.sock|listen = 9000|g" /etc/php/${VERSION}/fpm/pool.d/www.conf' ;
	echo "RUN wget https://wordpress.org/latest.zip && unzip latest.zip && cp -rf wordpress/* . && rm -rf wordpress latest.zip && rm -rf wp-config-sample.php && chmod -R 777 wp-content" ;
	echo "RUN mkdir -p /run/php/" ;
	echo "COPY ./tools/script.sh ." ;
	echo "RUN chmod +x script.sh && ./script.sh" ;
	echo 'CMD ["/usr/sbin/php-fpm7.4", "-F"]' ; } > ./requirements/wordpress/Dockerfile

	{ echo "#!/bin/sh" ;
	echo "cat << EOF > /var/www/wp-config.php" ;
	echo "<?php" ;
	echo "define( 'DB_NAME', '"'$MYSQL_DATABASE'"' );" ;
	echo "define( 'DB_USER', '"'$MYSQL_USER'"' );" ;
	echo "define( 'DB_PASSWORD', '"'$MYSQL_PASSWORD'"' );" ;
	echo "define( 'DB_HOST', 'mariadb' );" ;
	echo "define( 'DB_CHARSET', 'utf8' );" ;
	echo "define( 'DB_COLLATE', '' );" ;
	echo "define('FS_METHOD','direct');" ;
	echo '\\$table_prefix = '"'wp_'"';' ;
	echo "define( 'WP_DEBUG', false );" ;
	echo "define( 'WP_REDIS_HOST', 'redis' );" ;
	echo "define( 'WP_REDIS_PORT', 6379 );" ;
	echo "define( 'WP_CACHE', true );" ;
	echo "if ( ! defined( 'ABSPATH' ) ) {" ;
	echo "define( 'ABSPATH', __DIR__ . '/' );}" ;
	echo "require_once ABSPATH . 'wp-settings.php';" ;
	echo 'EOF' ; } > ./requirements/wordpress/tools/script.sh

fi


echo "Setup Redis ? (y/n)"

read answer

if [ "$answer" = "y"  ] || [ "$answer" = "Y"  ]
then
	# Setup redis

	{ echo "FROM debian:stable" ;
	echo "RUN apt update -y && apt upgrade -y" ;
	echo "RUN apt install -y redis redis-server" ;
	echo 'RUN sed -i "s|bind 127.0.0.1 -::1|#bind 127.0.0.1 -::1|g" /etc/redis/redis.conf' ;
	echo 'RUN sed -i "s|# maxmemory <bytes>|maxmemory 100mb|g" /etc/redis/redis.conf' ;
	echo 'RUN sed -i "s|# maxmemory-policy noeviction|maxmemory-policy allkeys-lru|g" /etc/redis/redis.conf' ;
	echo 'CMD ["redis-server", "--protected-mode no" ]' ; } > ./requirements/bonus/redis/Dockerfile
fi


echo "Setup FTP ? (y/n)"

read answer

if [ "$answer" = "y"  ] || [ "$answer" = "Y"  ]
then
	# Setup ftp

	{ echo "FROM debian:stable" ;
	echo "RUN apt update -y && apt upgrade -y" ;
	echo "RUN apt install -y vsftpd" ;
	echo "COPY ./conf/vsftpd.conf /etc/vsftpd.conf" ;
	echo "COPY ./tools/script.sh ." ;
	echo "RUN chmod +x script.sh" ;
	echo "EXPOSE 21";
	echo 'CMD ["./script.sh"]' ; } > ./requirements/bonus/ftp/Dockerfile

	{ echo "#!/bin/sh" ;
	echo 'mkdir -p /var/run/vsftpd/empty' ;
	echo 'adduser --home /var/www ${FTP_USER}' ;
	echo 'echo ${FTP_USER}:${FTP_PASSWORD} | chpasswd' ;
	echo 'adduser ${FTP_USER} root' ;
	echo "exec /usr/sbin/vsftpd /etc/vsftpd.conf" ; } > ./requirements/bonus/ftp/tools/script.sh

	wget -O ./requirements/bonus/ftp/conf/vsftpd.conf https://raw.githubusercontent.com/drabi-he/1337-Cursus/master/LVL5/inception/extra/vsftpd.conf

	sed -i "s|#local_enable=YES|local_enable=YES|g" ./requirements/bonus/ftp/conf/vsftpd.conf
	sed -i "s|#write_enable=YES|write_enable=YES|g" ./requirements/bonus/ftp/conf/vsftpd.conf
	sed -i "s|#chroot_local_user=YES|chroot_local_user=YES|g" ./requirements/bonus/ftp/conf/vsftpd.conf
	echo " " >> ./requirements/bonus/ftp/conf/vsftpd.conf
	echo "allow_writeable_chroot=YES" >> ./requirements/bonus/ftp/conf/vsftpd.conf
	echo "seccomp_sandbox=NO" >> ./requirements/bonus/ftp/conf/vsftpd.conf
	echo "pasv_enable=YES" >> ./requirements/bonus/ftp/conf/vsftpd.conf
fi

echo "Setup Adminer ? (y/n)"

read answer

if [ "$answer" = "y"  ] || [ "$answer" = "Y"  ]
then
	# Setup Adminer

	{ echo "FROM debian:stable" ;
	echo "RUN apt update -y && apt upgrade -y" ;
	echo "RUN apt install -y php php-common php-iconv php-json php-gd php-curl php-xml php-mysqli php-imap php-cgi php-pdo php-soap php-posix php-ldap php-ctype php-dom php-simplexml wget" ;
	echo "WORKDIR /var/www" ;
	echo "RUN wget https://github.com/vrana/adminer/releases/download/v4.8.1/adminer-4.8.1.php" ;
	echo "RUN mv adminer-4.8.1.php index.php" ;
	echo "EXPOSE 8080" ;
	echo 'CMD [ "php", "-S", "[::]:8080" , "-t", "/var/www" ]' ; } > ./requirements/bonus/adminer/Dockerfile
fi

echo "Setup static WebSite ? (y/n)"

read answer

if [ "$answer" = "y"  ] || [ "$answer" = "Y"  ]
then
	# Setup website

	{ echo "FROM debian:stable" ;
	echo "RUN apt update -y && apt upgrade -y" ;
	echo "RUN apt install -y nginx" ;
	echo "COPY ./conf/nginx.conf /etc/nginx/nginx.conf" ;
	echo "COPY ./tools/* /var/www/" ;
	echo "EXPOSE 3000" ;
	echo 'CMD [ "nginx", "-g", "daemon off;" ]' ; } > ./requirements/bonus/website/Dockerfile

	{ echo "events {}" ;
	echo "http {" ;
	echo "	server {" ;
	echo "		listen 3000;" ;
	echo "		listen [::]:3000;" ;
	echo "		server_name server;" ;
	echo "		root /var/www/;" ;
	echo "		index index.html;" ;
	echo "		location / {" ;
	echo "				root /var/www/;" ;
	echo "				index index.html;" ;
	echo "		}" ;
	echo "	}" ;
	echo "}"; } > ./requirements/bonus/website/conf/nginx.conf

	{
	echo '<!DOCTYPE html>' ;
	echo '<html lang="en">' ;
	echo '<head>' ;
	echo '	<meta charset="UTF-8">' ;
	echo '	<meta http-equiv="X-UA-Compatible" content="IE=edge">' ;
	echo '	<meta name="viewport" content="width=device-width, initial-scale=1.0">' ;
	echo '	<title>static website</title>' ;
	echo '</head>' ;
	echo '<body>' ;
	echo '	<h1> this is our static website for this insane project </h1>' ;
	echo '	<h2> this is our static website for this insane project </h2>' ;
	echo '	<h3> this is our static website for this insane project </h3>' ;
	echo '	<h4> this is our static website for this insane project </h4>' ;
	echo '	<h5> this is our static website for this insane project </h5>' ;
	echo '	<h6> this is our static website for this insane project </h6>' ;
	echo '</body>' ;
	echo '</html>' ;
	} > ./requirements/bonus/website/tools/index.html
fi

echo "Setup Portainer ? (y/n)"

read answer

if [ "$answer" = "y"  ] || [ "$answer" = "Y"  ]
then
	{ echo 'FROM debian:stable'
	echo 'RUN apt update -y && apt upgrade -y'
	echo 'RUN apt install -y curl tar'
	echo 'RUN mkdir -p /var/lib/portainer'
	echo 'RUN adduser --home /var/lib/portainer portainer'
	echo 'RUN curl -sSL https://github.com/portainer/portainer/releases/download/2.16.2/portainer-2.16.2-linux-amd64.tar.gz | tar -xzo -C /usr/local'
	echo 'CMD ["/usr/local/portainer/portainer"]'
	} > ./requirements/bonus/portainer/Dockerfile
fi

echo "Setup docker-compose ? (y/n)"

read answer

if [ "$answer" = "y"  ] || [ "$answer" = "Y"  ]
then
	# Setup Docker Compose

	{ echo "version: '3'" ;
	echo '' ;
	echo 'services:' ;
	echo '  nginx:' ;
	echo '    build:' ;
	echo '      context: ./requirements/nginx' ;
	echo '      dockerfile: Dockerfile' ;
	echo '    image: nginx' ;
	echo '    container_name: nginx' ;
	echo '    depends_on:' ;
	echo '      - wordpress' ;
	echo '    ports:' ;
	echo '      - "443:443"' ;
	echo '    networks:' ;
	echo '      - inception' ;
	echo '    volumes:' ;
	echo '      - ./requirements/nginx/conf/nginx.conf:/etc/nginx/sites-available/default' ;
	echo '      - ./requirements/tools:/etc/nginx/ssl/' ;
	echo '      - wp-data:/var/www/' ;
	echo '    restart: always' ;
	echo '' ;
	echo '  mariadb:' ;
	echo '    build:' ;
	echo '      context: ./requirements/mariadb' ;
	echo '      dockerfile: Dockerfile' ;
	echo '    image: mariadb' ;
	echo '    container_name: mariadb' ;
	echo '    volumes:' ;
	echo '      - db-data:/var/lib/mysql' ;
	echo '    environment:' ;
	echo '      MYSQL_DATABASE: ${MYSQL_DATABASE}' ;
	echo '      MYSQL_ROOT_PASSWORD: ${MYSQL_ROOT_PASSWORD}' ;
	echo '      MYSQL_USER: ${MYSQL_USER}' ;
	echo '      MYSQL_PASSWORD: ${MYSQL_PASSWORD}' ;
	echo '    networks:' ;
	echo '      - inception' ;
	echo '    restart: always' ;
	echo '' ;
	echo '  wordpress:' ;
	echo '    build:' ;
	echo '      context: ./requirements/wordpress' ;
	echo '      dockerfile: Dockerfile' ;
	echo '      args:' ;
	echo '        MYSQL_DATABASE: ${MYSQL_DATABASE}' ;
	echo '        MYSQL_ROOT_PASSWORD: ${MYSQL_ROOT_PASSWORD}' ;
	echo '        MYSQL_USER: ${MYSQL_USER}' ;
	echo '        MYSQL_PASSWORD: ${MYSQL_PASSWORD}' ;
	echo '    image: wordpress' ;
	echo '    container_name: wordpress' ;
	echo '    depends_on:' ;
	echo '      - mariadb' ;
	echo '    volumes:' ;
	echo '      - wp-data:/var/www/' ;
	echo '    networks:' ;
	echo '      - inception' ;
	echo '    restart: always' ;
	echo '' ;
	echo '  redis:' ;
	echo '    build:' ;
	echo '      context: ./requirements/bonus/redis' ;
	echo '      dockerfile: Dockerfile' ;
	echo '    image: redis' ;
	echo '    container_name: redis' ;
	echo '    ports:' ;
	echo '      - "6379:6379"' ;
	echo '    volumes:' ;
	echo '      - wp-data:/var/www/' ;
	echo '    networks:' ;
	echo '      - inception' ;
	echo '    restart: always' ;
	echo '' ;
	echo '  ftp:' ;
	echo '    build:' ;
	echo '      context: ./requirements/bonus/ftp' ;
	echo '      dockerfile: Dockerfile' ;
	echo '    image: ftp' ;
	echo '    container_name: ftp' ;
	echo '    environment:' ;
	echo '      FTP_USER: ${FTP_USER}' ;
	echo '      FTP_PASSWORD: ${FTP_PASSWORD}' ;
	echo '    ports:' ;
	echo '      - "21:21"' ;
	echo '    volumes:' ;
	echo '      - wp-data:/var/www/' ;
	echo '    networks:' ;
	echo '      - inception' ;
	echo '    restart: always' ;
	echo '' ;
	echo '  adminer:' ;
	echo '    build:' ;
	echo '      context: ./requirements/bonus/adminer' ;
	echo '      dockerfile: Dockerfile' ;
	echo '    image: adminer' ;
	echo '    container_name: adminer' ;
	echo '    depends_on:' ;
	echo '      - mariadb' ;
	echo '    ports:' ;
	echo '      - "8080:8080"' ;
	echo '    networks:' ;
	echo '      - inception' ;
	echo '    restart: always' ;
	echo '' ;
	echo '  website:' ;
	echo '    build:' ;
	echo '      context: ./requirements/bonus/website' ;
	echo '      dockerfile: Dockerfile' ;
	echo '    image: website' ;
	echo '    container_name: website' ;
	echo '    ports:' ;
	echo '      - "3000:3000"' ;
	echo '    networks:' ;
	echo '      - inception' ;
	echo '    restart: always' ;
	echo '' ;
	echo '  portainer:' ;
	echo '    build:' ;
	echo '      context: ./requirements/bonus/portainer' ;
	echo '      dockerfile: Dockerfile' ;
	echo '    image: portainer' ;
	echo '    container_name: portainer' ;
	echo '    ports:' ;
	echo '      - "9443:9443"' ;
	echo '    volumes:' ;
	echo '      - "/var/run/docker.sock:/var/run/docker.sock:ro"' ;
	echo '      - portainer-data:/data' ;
	echo '    networks:' ;
	echo '      - inception' ;
	echo '    restart: always' ;
	echo '' ;
	echo 'volumes:' ;
	echo '  wp-data:' ;
	echo '    driver_opts:' ;
	echo '      o: bind' ;
	echo '      type: none' ;
	echo '      device: /home/${USER}/data/wordpress' ;
	echo '' ;
	echo '  db-data:' ;
	echo '    driver_opts:' ;
	echo '      o: bind' ;
	echo '      type: none' ;
	echo '      device: /home/${USER}/data/mariadb' ;
	echo '' ;
	echo '  portainer-data:' ;
	echo '    driver_opts:' ;
	echo '      o: bind' ;
	echo '      type: none' ;
	echo '      device: /home/${USER}/data/portainer' ;
	echo '' ;
	echo 'networks:' ;
	echo '  inception:' ;
	echo '    driver: bridge ' ; } > ./docker-compose.yml
fi


echo "Setup Makefile? (y/n)"

read answer

if [ "$answer" = "y"  ] || [ "$answer" = "Y"  ]
then
	# Setup Makefile
	cd ..
	{ echo 'NAME = inception' ;
	echo '' ;
	echo 'all:' ;
	echo '	@printf "Starting ${NAME} ...\\n"' ;
	echo '	@sh ./srcs/requirements/tools/script.sh' ;
	echo '	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env up -d' ;
	echo '' ;
	echo 'build:' ;
	echo '	@printf "Building ${NAME} ...\\n"' ;
	echo '	@sh ./srcs/requirements/tools/script.sh' ;
	echo '	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env up -d --build' ;
	echo '' ;
	echo 'start:' ;
	echo '	@printf "Starting ${NAME} ...\\n"' ;
	echo '	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env start' ;
	echo '' ;
	echo 'stop:' ;
	echo '	@printf "Stopping ${NAME} ...\\n"' ;
	echo '	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env stop' ;
	echo '' ;
	echo 'down:' ;
	echo '	@printf "Shuting Down ${NAME} ...\\n"' ;
	echo '	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env down' ;
	echo '' ;
	echo 're: down' ;
	echo '	printf "ReBuilding ${NAME} ...\\n"' ;
	echo '	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env up -d --build' ;
	echo '' ;
	echo 'clean: down' ;
	echo '	@printf "Cleaning ${name} ...\\n"' ;
	echo '	@docker system prune -a' ;
	echo '	@sudo rm -rf ~/data' ;
	echo '' ;
	echo 'fclean:' ;
	echo '	@printf "Total Cleaning ...\\n"' ;
	echo '	@docker stop $$(docker ps -aq)' ;
	echo '	@docker system prune --all --force --volumes' ;
	echo '	@docker network prune --force' ;
	echo '	@docker volume prune --force' ;
	echo '	@sudo rm -rf ~/data' ; } > ./Makefile

fi