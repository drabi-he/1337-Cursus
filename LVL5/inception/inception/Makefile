NAME = inception

all:
	@printf "Starting ${NAME} ..."
	@sh ./srcs/requirements/tools/script.sh
	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env up -d

build:
	@printf "Building ${NAME} ..."
	@sh ./srcs/requirements/tools/script.sh
	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env up -d --build

down:
	@printf "Shuting Down ${NAME} ..."
	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env down

re: down
	printf "ReBuilding ${NAME} ..."
	@docker-compose -f ./srcs/docker-compose.yml --env-file ./srcs/.env up -d --build

clean: down
	@printf "Cleaning ${name} ..."
	@docker system prune -a
	@sudo rm -rf ~/data

fclean:
	@printf "Total Cleaning ..."
	@docker stop $$(docker ps -aq)
	@docker system prune --all --force --volumes
	@docker network prune --force
	@docker volume prune --force
	@sudo rm -rf ~/data
