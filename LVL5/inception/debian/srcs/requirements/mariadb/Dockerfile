FROM debian:buster

RUN apt update -y && apt upgrade -y

RUN apt install -y mariadb-server mariadb-client

RUN mkdir -p /var/run/mysqld

RUN chown -R mysql:mysql /var/run/mysqld

RUN chmod 777 /var/run/mysqld

COPY ./tools/script.sh /

COPY ./conf/docker.cnf /etc/mysql/mariadb.conf.d/

RUN sed -i "s|bind-address            = 127.0.0.1|bind-address            = 0.0.0.0|g" /etc/mysql/mariadb.conf.d/50-server.cnf

RUN chmod +x /script.sh

EXPOSE 3306

CMD ["/script.sh"]
