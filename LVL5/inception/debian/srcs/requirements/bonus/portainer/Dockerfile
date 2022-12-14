FROM debian:stable
RUN apt update -y && apt upgrade -y
RUN apt install -y curl tar
RUN mkdir -p /var/lib/portainer
RUN adduser --home /var/lib/portainer portainer
RUN curl -sSL https://github.com/portainer/portainer/releases/download/2.16.2/portainer-2.16.2-linux-amd64.tar.gz | tar -xzo -C /usr/local
CMD ["/usr/local/portainer/portainer"]
