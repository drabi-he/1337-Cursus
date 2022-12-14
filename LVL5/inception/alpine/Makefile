NAME = inception

all:
	@printf "Starting ${NAME} ...\n"
	@sh ./srcs/requirements/tools/script.sh
	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env up -d

build:
	@printf "Building ${NAME} ...\n"
	@sh ./srcs/requirements/tools/script.sh
	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env up -d --build

start:
	@printf "Starting ${NAME} ...\n"
	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env start

stop:
	@printf "Stopping ${NAME} ...\n"
	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env stop

down:
	@printf "Shuting Down ${NAME} ...\n"
	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env down

re: down
	printf "ReBuilding ${NAME} ...\n"
	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env up -d --build

clean: down
	@printf "Cleaning ${name} ...\n"
	@docker system prune -a
	@sudo rm -rf ~/data

fclean:
	@printf "Total Cleaning ...\n"
	@docker stop $$(docker ps -aq)
	@docker system prune --all --force --volumes
	@docker network prune --force
	@docker volume prune --force
	@sudo rm -rf ~/data
