FROM alpine:3.17
RUN apk update && apk upgrade
RUN apk add curl tar
RUN mkdir -p /var/lib/portainer
RUN adduser -h /var/lib/portainer -D portainer
RUN curl -sSL https://github.com/portainer/portainer/releases/download/2.16.2/portainer-2.16.2-linux-amd64.tar.gz | tar -xzo -C /usr/local
CMD ["/usr/local/portainer/portainer"]
