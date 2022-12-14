FROM alpine:3.17
RUN apk update && apk upgrade
RUN apk add --no-cache mariadb mariadb-client openrc && openrc
RUN mkdir -p /run/openrc && touch /run/openrc/softlevel
RUN mkdir -p /var/run/mysqld && chown -R mysql /var/run/mysqld && chmod -R 777 /var/run/mysqld
RUN sed -i "s|skip-networking|skip-networking=0|g" /etc/my.cnf.d/mariadb-server.cnf
COPY ./conf/docker.cnf /etc/my.cnf.d/
COPY ./tools/script.sh .
RUN chmod +x script.sh
CMD ["sh", "script.sh"]
