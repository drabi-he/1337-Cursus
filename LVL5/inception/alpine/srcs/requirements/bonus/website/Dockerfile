FROM alpine:3.17
RUN apk update && apk upgrade
RUN apk add --no-cache nginx
COPY ./conf/nginx.conf /etc/nginx/nginx.conf
COPY ./tools/* /var/www/
EXPOSE 3000
CMD [ "nginx", "-g", "daemon off;" ]
