FROM debian:stable
RUN apt update -y && apt upgrade -y
RUN apt install -y php php-common php-iconv php-json php-gd php-curl php-xml php-mysqli php-imap php-cgi php-pdo php-soap php-posix php-ldap php-ctype php-dom php-simplexml wget
WORKDIR /var/www
RUN wget https://github.com/vrana/adminer/releases/download/v4.8.1/adminer-4.8.1.php
RUN mv adminer-4.8.1.php index.php
EXPOSE 8080
CMD [ "php", "-S", "[::]:8080" , "-t", "/var/www" ]
