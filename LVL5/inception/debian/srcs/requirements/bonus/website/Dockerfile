FROM debian:stable
RUN apt update -y && apt upgrade -y
RUN apt install -y nginx
COPY ./conf/nginx.conf /etc/nginx/nginx.conf
COPY ./tools/* /var/www/
EXPOSE 3000
CMD [ "nginx", "-g", "daemon off;" ]
