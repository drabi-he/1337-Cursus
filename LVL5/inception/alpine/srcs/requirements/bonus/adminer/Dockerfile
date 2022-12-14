FROM alpine:3.17
RUN apk update && apk upgrade
RUN apk add --no-cache php php-common php-session php-iconv php-json php-gd php-curl php-xml php-mysqli php-imap php-cgi fcgi php-pdo php-pdo_mysql php-soap php-posix php-gettext php-ldap php-ctype php-dom php-simplexml wget
WORKDIR /var/www
RUN wget https://github.com/vrana/adminer/releases/download/v4.8.1/adminer-4.8.1.php
RUN mv adminer-4.8.1.php index.php
EXPOSE 8080
CMD [ "php", "-S", "[::]:8080" , "-t", "/var/www" ]
