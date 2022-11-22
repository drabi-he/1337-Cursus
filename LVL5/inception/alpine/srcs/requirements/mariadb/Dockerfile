FROM alpine:latest

RUN apk update && apk upgrade

RUN apk add mariadb mariadb-client openrc && openrc

RUN touch /run/openrc/softlevel

RUN mkdir -p /var/run/mysqld

RUN chown -R mysql:mysql /var/run/mysqld

RUN chmod 777 /var/run/mysqld

COPY ./tools/script.sh /

COPY ./conf/docker.cnf /etc/my.cnf.d/

RUN sed -i "s|skip-networking|skip-networking=0|g" /etc/my.cnf.d/mariadb-server.cnf

RUN chmod +x /script.sh

EXPOSE 3306

CMD ["/script.sh"]