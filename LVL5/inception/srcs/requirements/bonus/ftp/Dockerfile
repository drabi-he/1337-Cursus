FROM alpine:3.17
RUN apk update && apk upgrade
RUN apk add --no-cache vsftpd
COPY ./conf/vsftpd.conf /etc/vsftpd/vsftpd.conf
COPY ./tools/script.sh .
RUN chmod +x script.sh
EXPOSE 21
CMD ["./script.sh"]
