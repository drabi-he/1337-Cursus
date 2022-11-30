#!/bin/sh

echo "Setup you machine ? (y/n)"

read answer

if [ "$answer" = "y"  ] || [ "$answer" = "Y"  ]
then
	apt update -y && apt upgrade -y
	apt install -y sudo ufw docker docker-compose make openbox xinit kitty firefox-esr wget curl libnss3-tools
	sed -i "s|#Port 22|Port 42|g" /etc/ssh/sshd_config
	sed -i "s|#PermitRootLogin prohibit-password|PermitRootLogin yes|g" /etc/ssh/sshd_config
	service ssh restart
	service sshd restart
	ufw enable
	ufw allow 42
	ufw allow 80
	ufw allow 443
	curl -s https://api.github.com/repos/FiloSottile/mkcert/releases/latest| grep browser_download_url | grep linux-amd64 | cut -d '"' -f 4 | wget -qi -
	mv mkcert-v*-linux-amd64 mkcert
	chmod a+x mkcert
	sudo mv mkcert /usr/local/bin/
fi


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
mkdir inception/srcs/requirements/nginx/conf
touch inception/srcs/requirements/nginx/conf/nginx.conf
mkdir inception/srcs/requirements/wordpress
touch inception/srcs/requirements/wordpress/.dockerignore
touch inception/srcs/requirements/wordpress/Dockerfile
mkdir inception/srcs/requirements/wordpress/conf
mkdir inception/srcs/requirements/wordpress/tools
touch inception/srcs/requirements/wordpress/tools/script.sh
mkdir inception/srcs/requirements/bonus
mkdir inception/srcs/requirements/bonus/redis
touch inception/srcs/requirements/bonus/redis/.dockerignore
touch inception/srcs/requirements/bonus/redis/Dockerfile
mkdir inception/srcs/requirements/bonus/redis/conf
mkdir inception/srcs/requirements/bonus/redis/tools
mkdir inception/srcs/requirements/bonus/ftp
touch inception/srcs/requirements/bonus/ftp/.dockerignore
touch inception/srcs/requirements/bonus/ftp/Dockerfile
mkdir inception/srcs/requirements/bonus/ftp/conf
mkdir inception/srcs/requirements/bonus/ftp/tools
mkdir inception/srcs/requirements/bonus/website
touch inception/srcs/requirements/bonus/website/.dockerignore
touch inception/srcs/requirements/bonus/website/Dockerfile
mkdir inception/srcs/requirements/bonus/website/conf
mkdir inception/srcs/requirements/bonus/website/tools
mkdir inception/srcs/requirements/bonus/adminer
touch inception/srcs/requirements/bonus/adminer/.dockerignore
touch inception/srcs/requirements/bonus/adminer/Dockerfile
mkdir inception/srcs/requirements/bonus/adminer/conf
mkdir inception/srcs/requirements/bonus/adminer/tools

_CertName="self-signed"
_DB_NAME="wordpress"
_DB_USER="wpuser"
_DB_PASS="wppass"
_DB_ROOT_PASS="rootpass"
_DOMAIN_NAME="localhost"

echo "Setup environement variables"
echo "self-signed certificate name : default ($_CertName)"

read _CertName

echo "Database name : default ($_DB_NAME)"

read _DB_NAME

echo "Database user : default ($_DB_USER)"

read _DB_USER

echo "Database password : default ($_DB_PASS)"

read _DB_PASS

echo "Database root password : default ($_DB_ROOT_PASS)"

read _DB_ROOT_PASS

echo "Domain name : default ($_DOMAIN_NAME)"

read _DOMAIN_NAME

# Setup environment variables and .dockerignore
echo "DOMAIN_NAME=$_CertName" > inception/srcs/.env
echo "_CERT=./requirements/tools/$_CertName.crt" >> inception/srcs/.env
echo "_KEY=./requirements/tools/$_CertName.key" >> inception/srcs/.env
echo "MYSQL_DATABASE=$_DB_NAME" >> inception/srcs/.env
echo "MYSQL_ROOT_PASSWORD=$_DB_ROOT_PASS" >> inception/srcs/.env
echo "MYSQL_USER=$_DB_USER" >> inception/srcs/.env
echo "MYSQL_PASSWORD=$_DB_PASS" >> inception/srcs/.env
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
cd inception/srcs/requirements/tools
mkcert $_CertName
mv $_CertName-key.pem $_CertName.key
mv $_CertName.pem $_CertName.crt
cd ../..

# Directory script.sh
{ echo '#!/bin/sh' ;
echo 'mkdir ~/data' ;
echo 'mkdir ~/data/mariadb' ;
echo 'mkdir ~/data/wordpress' ;
} > ./requirements/tools/script.sh

chmod +x ./requirements/tools/script.sh

fi

echo "Setup inception services ? (y/n)"

read answer

if [ "$answer" = "y"  ] || [ "$answer" = "Y"  ]
then

# Setup NGINX

{ echo "FROM alpine:3.17" ;
echo "RUN apk update && apk upgrade" ;
echo "RUN apk add --no-cache nginx" ;
echo "EXPOSE 443" ;
echo 'CMD ["nginx", "-g", "daemon off;"]' ; } > ./requirements/nginx/Dockerfile

{ echo "server {" ;
echo "listen 443 ssl;" ;
echo "server_name $_DOMAIN_NAME www.$_DOMAIN_NAME;" ;
echo "ssl_certificate /etc/nginx/ssl/$_CertName.crt;" ;
echo "ssl_certificate_key /etc/nginx/ssl/$_CertName.key;" ;
echo "ssl_protocols TLSv1.2 TLSv1.3;" ;
echo "root /var/www/;";
echo "index index.php index.html;" ;
echo "location / {" ;
echo 'try_files $uri /index.php?$args;' ;
echo 'add_header Last-Modified $date_gmt;' ;
echo "add_header Cache-Control 'no-store, no-cache';" ;
echo "if_modified_since off;" ;
echo "expires off;" ;
echo "etag off;" ;
echo "}" ;
echo "location ~ \.php$ {";
echo "fastcgi_split_path_info ^(.+\.php)(/.+)$;";
echo "fastcgi_pass wordpress:9000;";
echo "fastcgi_index index.php;";
echo "include fastcgi_params;";
echo 'fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;';
echo 'fastcgi_param PATH_INFO $fastcgi_path_info;';
echo "}";
echo "}"; } > ./requirements/nginx/conf/nginx.conf

# Setup MariaDB

{ echo "FROM alpine:3.17" ;
echo "RUN apk update && apk upgrade" ;
echo "RUN apk add --no-cache mariadb mariadb-client openrc && openrc" ;
echo "RUN mkdir -p /run/openrc && touch /run/openrc/softlevel" ;
echo "RUN mkdir -p /var/run/mysqld && chown -R mysql /var/run/mysqld && chmod -R 777 /var/run/mysqld" ;
echo 'RUN sed -i "s|skip-networking|skip-networking=0|g" /etc/my.cnf.d/mariadb-server.cnf' ;
echo "COPY ./conf/docker.cnf /etc/my.cnf.d/" ;
echo "COPY ./tools/script.sh ." ;
echo "RUN chmod +x script.sh" ;
echo 'CMD ["sh", "script.sh"]' ; } > ./requirements/mariadb/Dockerfile

{ echo "[mysqld]" ;
echo "skip-host-cache" ;
echo "skip-name-resolve" ;
echo "bind-address=0.0.0.0" ; } > ./requirements/mariadb/conf/docker.cnf

{ echo "#!/bin/sh" ;
echo "mysql_install_db --user=mysql --datadir=/var/lib/mysql" ;
echo "rc-service mariadb start" ;
echo 'if [ ! -d "/var/lib/mysql/$MYSQL_DATABASE" ]' ;
echo "then" ;
echo 'mysql -u root -e "SET PASSWORD FOR '"'root'@'localhost'"' = PASSWORD('"'"'$MYSQL_ROOT_PASSWORD'"'"');"' ;
echo 'mysql -u root -p$MYSQL_ROOT_PASSWORD -e "DROP USER '"''@'localhost'"';"' ;
echo 'mysql -u root -p$MYSQL_ROOT_PASSWORD -e "DROP USER '"''@'"'$(hostname)'"'"';"' ;
echo 'mysql -u root -p$MYSQL_ROOT_PASSWORD -e "DROP DATABASE IF EXISTS test;"' ;
echo 'mysql -u root -p$MYSQL_ROOT_PASSWORD -e "CREATE USER '"'root'@'%' IDENTIFIED BY ""'"'$MYSQL_ROOT_PASSWORD'"'"';"' ;
echo 'mysql -u root -p$MYSQL_ROOT_PASSWORD -e "GRANT ALL ON *.* TO '"'root'@'%' IDENTIFIED BY '"'$MYSQL_ROOT_PASSWORD'"'"';"' ;
echo 'mysql -u root -p$MYSQL_ROOT_PASSWORD -e "CREATE DATABASE IF NOT EXISTS $MYSQL_DATABASE; GRANT ALL ON $MYSQL_DATABASE.* TO '"'"'$MYSQL_USER'"'@'%' IDENTIFIED BY '"'$MYSQL_PASSWORD'"'"';"' ;
echo "fi" ;
echo "rc-service mariadb stop"
echo "exec mysqld --user=mysql" ; } > ./requirements/mariadb/tools/script.sh

# Setup Wordpress

{ echo "FROM alpine:3.17" ;
echo "ARG MYSQL_DATABASE MYSQL_USER MYSQL_PASSWORD" ;
echo "WORKDIR /var/www" ;
echo "RUN apk update && apk upgrade" ;
echo "RUN apk update && apk upgrade && apk add --no-cache php php-fpm php-mysqli php-json php-curl php-dom php-exif php-fileinfo php-mbstring php-openssl php-xml php-zip wget unzip" ;
echo 'RUN sed -i "s|listen = 127.0.0.1:9000|listen = 9000|g" /etc/php81/php-fpm.d/www.conf' ;
echo "RUN wget https://wordpress.org/latest.zip && unzip latest.zip && cp -rf wordpress/* . && rm -rf wordpress latest.zip && rm -rf wp-config-sample.php && chmod -R 777 wp-content" ;
echo "COPY ./tools/script.sh ." ;
echo "RUN chmod +x script.sh && ./script.sh" ;
echo 'CMD ["/usr/sbin/php-fpm81", "-F"]' ; } > ./requirements/wordpress/Dockerfile

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
echo '\$table_prefix = '"'wp_'"';' ;
echo "define( 'WP_DEBUG', false );" ;
echo "if ( ! defined( 'ABSPATH' ) ) {" ;
echo "define( 'ABSPATH', __DIR__ . '/' );}" ;
echo "require_once ABSPATH . 'wp-settings.php';" ;
echo 'EOF' ; } > ./requirements/wordpress/tools/script.sh

# Setup Docker Compose

{ echo "version: '3'" ;
echo '' ;
echo 'services:' ;
echo '  nginx:' ;
echo '    build:' ;
echo '      context: ./requirements/nginx' ;
echo '      dockerfile: Dockerfile' ;
echo '    container_name: nginx' ;
echo '    depends_on:' ;
echo '      - wordpress' ;
echo '    ports:' ;
echo '      - "443:443"' ;
echo '    networks:' ;
echo '      - inception' ;
echo '    volumes:' ;
echo '      - ./requirements/nginx/conf/:/etc/nginx/http.d/' ;
echo '      - ./requirements/tools:/etc/nginx/ssl/' ;
echo '      - wp-data:/var/www/' ;
echo '    restart: always' ;
echo '' ;
echo '  mariadb:' ;
echo '    build:' ;
echo '      context: ./requirements/mariadb' ;
echo '      dockerfile: Dockerfile' ;
echo '    container_name: mariadb' ;
echo '    environment:' ;
echo '      MYSQL_DATABASE: ${MYSQL_DATABASE}' ;
echo '      MYSQL_ROOT_PASSWORD: ${MYSQL_ROOT_PASSWORD}' ;
echo '      MYSQL_USER: ${MYSQL_USER}' ;
echo '      MYSQL_PASSWORD: ${MYSQL_PASSWORD}' ;
echo '    ports:' ;
echo '      - "3306:3306"' ;
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
echo '    container_name: wordpress' ;
echo '    depends_on:' ;
echo '      - mariadb' ;
echo '    environment:' ;
echo '      MYSQL_DATABASE: ${MYSQL_DATABASE}' ;
echo '      MYSQL_ROOT_PASSWORD: ${MYSQL_ROOT_PASSWORD}' ;
echo '      MYSQL_USER: ${MYSQL_USER}' ;
echo '      MYSQL_PASSWORD: ${MYSQL_PASSWORD}' ;
echo '    restart: always' ;
echo '    networks:' ;
echo '      - inception' ;
echo '    volumes:' ;
echo '      - wp-data:/var/www/' ;
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
echo 'networks:' ;
echo '    inception:' ;
echo '        driver: bridge ' ; } > ./docker-compose.yml

# Setup Makefile
cd ..
{ echo 'NAME = inception' ;
echo '' ;
echo 'all:' ;
echo '	@printf "Starting ${NAME} ..."' ;
echo '	@sh ./srcs/requirements/tools/script.sh' ;
echo '	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env up -d' ;
echo '' ;
echo 'build:' ;
echo '	@printf "Building ${NAME} ..."' ;
echo '	@sh ./srcs/requirements/tools/script.sh' ;
echo '	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env up -d --build' ;
echo '' ;
echo 'down:' ;
echo '	@printf "Shuting Down ${NAME} ..."' ;
echo '	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env down' ;
echo '' ;
echo 're: down' ;
echo '	printf "ReBuilding ${NAME} ..."' ;
echo '	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env up -d --build' ;
echo '' ;
echo 'clean: down' ;
echo '	@printf "Cleaning ${name} ..."' ;
echo '	@docker system prune -a' ;
echo '	@sudo rm -rf ~/data' ;
echo '' ;
echo 'fclean:' ;
echo '	@printf "Total Cleaning ..."' ;
echo '	@docker stop $$(docker ps -aq)' ;
echo '	@docker system prune --all --force --volumes' ;
echo '	@docker network prune --force' ;
echo '	@docker volume prune --force' ;
echo '	@sudo rm -rf ~/data' ; } > ./Makefile

fi