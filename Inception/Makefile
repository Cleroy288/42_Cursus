DATA_DIR=~/data

# Define colors
GREEN=\033[0;32m
RED=\033[0;31m
NO_COLOR=\033[0m

all: build

build: down
	@echo "Creating directories..."
	@mkdir -p $(DATA_DIR)/mariadb_data && \
		echo "${GREEN}Success:${NO_COLOR} Created directory $(DATA_DIR)/mariadb_data" || \
		echo "${RED}Failed to create directory $(DATA_DIR)/mariadb_data${NO_COLOR}"
	@mkdir -p $(DATA_DIR)/wordpress_data && \
		echo "${GREEN}Success:${NO_COLOR} Created directory $(DATA_DIR)/wordpress_data" || \
		echo "${RED}Failed to create directory $(DATA_DIR)/wordpress_data${NO_COLOR}"
	@echo "Updating /etc/hosts..."
	@{ sudo sed -i '/chleroy.42.fr/d' /etc/hosts && sudo sed -i '1i127.0.0.1 chleroy.42.fr' /etc/hosts; } && \
		echo "${GREEN}Success:${NO_COLOR} Updated /etc/hosts" || \
		echo "${RED}Failed to update /etc/hosts${NO_COLOR}"
	@echo "Starting Docker containers..."
	@{ sudo docker-compose -f srcs/docker-compose.yml up --build; } && \
		echo "${GREEN}Success:${NO_COLOR} Docker containers started" || \
		echo "${RED}Failed to start Docker containers${NO_COLOR}"

up: down
	@echo "Starting services..."
	@{ mkdir -p $(DATA_DIR)/mariadb_data && mkdir -p $(DATA_DIR)/wordpress_data; } && \
		echo "${GREEN}Success:${NO_COLOR} Created data directories" || \
		echo "${RED}Failed to create data directories${NO_COLOR}"
	@{ sudo sed -i '/chleroy.42.fr/d' /etc/hosts && sudo sed -i '1i127.0.0.1 chleroy.42.fr' /etc/hosts; } && \
		echo "${GREEN}Success:${NO_COLOR} Updated /etc/hosts" || \
		echo "${RED}Failed to update /etc/hosts${NO_COLOR}"
	@{ sudo docker-compose -f srcs/docker-compose.yml up -d; } && \
		echo "${GREEN}Success:${NO_COLOR} Services started" || \
		echo "${RED}Failed to start services${NO_COLOR}"

down:
	@echo "Stopping Docker containers..."
	@{ sudo docker-compose -f srcs/docker-compose.yml down; } && \
		echo "${GREEN}Success:${NO_COLOR} Docker containers stopped" || \
		echo "${RED}Failed to stop Docker containers${NO_COLOR}"

clean:
	@echo "Cleaning up..."
	@{ sudo docker-compose -f srcs/docker-compose.yml down --rmi all --volumes && sudo rm -rf $(DATA_DIR)/mariadb_data && sudo rm -rf $(DATA_DIR)/wordpress_data; } && \
		echo "${GREEN}Success:${NO_COLOR} Cleaned up the environment" || \
		echo "${RED}Failed to clean up the environment${NO_COLOR}"
	@{ sudo sed -i '/chleroy.42.fr/d' /etc/hosts; } && \
		echo "${GREEN}Success:${NO_COLOR} Reverted changes in /etc/hosts" || \
		echo "${RED}Failed to revert changes in /etc/hosts${NO_COLOR}"

.PHONY: all build up down clean

