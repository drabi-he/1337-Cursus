FROM debian:stable
RUN apt update -y && apt upgrade -y
RUN apt install -y nginx
EXPOSE 443
CMD ["nginx", "-g", "daemon off;"]
