FROM alpine:3.17
RUN apk update && apk upgrade
RUN apk add --no-cache redis
RUN sed -i "s|bind 127.0.0.1 -::1|#bind 127.0.0.1 -::1|g" /etc/redis.conf
RUN sed -i "s|# maxmemory <bytes>|maxmemory 100mb|g" /etc/redis.conf
RUN sed -i "s|# maxmemory-policy noeviction|maxmemory-policy allkeys-lru|g" /etc/redis.conf
CMD ["redis-server", "/etc/redis.conf" , "--protected-mode no" ]
