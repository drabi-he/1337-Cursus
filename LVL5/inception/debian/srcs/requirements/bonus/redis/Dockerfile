FROM debian:stable
RUN apt update -y && apt upgrade -y
RUN apt install -y redis redis-server
RUN sed -i "s|bind 127.0.0.1 -::1|#bind 127.0.0.1 -::1|g" /etc/redis/redis.conf
RUN sed -i "s|# maxmemory <bytes>|maxmemory 100mb|g" /etc/redis/redis.conf
RUN sed -i "s|# maxmemory-policy noeviction|maxmemory-policy allkeys-lru|g" /etc/redis/redis.conf
CMD ["redis-server", "--protected-mode no" ]
