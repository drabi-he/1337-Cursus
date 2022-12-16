FROM alpine:3.17
ARG MYSQL_DATABASE MYSQL_USER MYSQL_PASSWORD
WORKDIR /var/www
RUN apk update && apk upgrade
RUN apk add --no-cache php php-fpm php-mysqli php-json php-curl php-dom php-exif php-fileinfo php-mbstring php-openssl php-xml php-zip wget unzip
RUN sed -i "s|listen = 127.0.0.1:9000|listen = 9000|g" /etc/php81/php-fpm.d/www.conf
RUN wget https://wordpress.org/latest.zip && unzip latest.zip && cp -rf wordpress/* . && rm -rf wordpress latest.zip && rm -rf wp-config-sample.php && chmod -R 777 wp-content
COPY ./tools/script.sh .
RUN chmod +x script.sh && ./script.sh
CMD ["/usr/sbin/php-fpm81", "-F"]
