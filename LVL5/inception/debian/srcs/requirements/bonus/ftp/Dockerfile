FROM debian:stable
RUN apt update -y && apt upgrade -y
RUN apt install -y vsftpd
COPY ./conf/vsftpd.conf /etc/vsftpd.conf
COPY ./tools/script.sh .
RUN chmod +x script.sh
EXPOSE 21
CMD ["./script.sh"]
