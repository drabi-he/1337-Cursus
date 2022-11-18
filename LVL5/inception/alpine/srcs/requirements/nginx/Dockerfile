FROM alpine:latest

RUN apk update && apk upgrade

RUN apk add nginx openssl

RUN openssl req -x509 -new -newkey rsa:2048 -nodes -keyout /etc/ssl/private/localhost.key -out /etc/ssl/private/localhost.crt -subj \
	"/C=MA/ST=Beni Mellal-Khenifra/L=Khouribga/O=42 Network/OU=IT/CN=localhost"

RUN mkdir /var/www/html

COPY ./conf/nginx.conf /etc/nginx/nginx.conf

COPY ./tools/index.html /var/www/html/

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]