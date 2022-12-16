FROM debian:stable
RUN apt update -y && apt upgrade -y
RUN apt install -y mariadb-server mariadb-client
RUN mkdir -p /var/run/mysqld && chown -R mysql /var/run/mysqld && chmod -R 777 /var/run/mysqld
RUN  sed -i "s|bind-address            = 127.0.0.1|bind-address            = 0.0.0.0|g" /etc/mysql/mariadb.conf.d/50-server.cnf
COPY ./tools/script.sh .
RUN chmod +x script.sh
CMD ["sh", "script.sh"]
