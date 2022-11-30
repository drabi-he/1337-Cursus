FROM alpine:3.17
RUN apk update && apk upgrade
RUN apk add --no-cache nginx
EXPOSE 443
CMD ["nginx", "-g", "daemon off;"]
