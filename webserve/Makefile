#NAME = Webserv
#
#SRC = main.cpp \
#		srcs/utils/utils.cpp \
#		srcs/parsing/verifyConfigFile.cpp \
#		srcs/parsing/nginx/*.cpp \
#		srcs/parsing/server/*.cpp \
#		srcs/exec/socket/*.cpp \
#		srcs/exec/client/*.cpp \
#		srcs/exec/server/*.cpp \
#
#
#
#FLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -O3
#
#all: $(NAME)
#
#$(NAME):
#	c++ $(FLAGS) $(SRC) -o $(NAME)
#
#clean:
#
#fclean: clean
#	rm -f $(NAME)
#
#re: fclean all
# NAME = Webserve
# DOCKER_IMG_NAME = webserve_img
# DOCKER_CONTAINER_NAME = webserve_container
# DOCKER_NETWORK_NAME = webserve_network

# SRC = main.cpp \
#       srcs/utils/utils.cpp \
#       srcs/parsing/verifyConfigFile.cpp \
#       srcs/parsing/nginx/*.cpp \
#       srcs/parsing/server/*.cpp \
#       srcs/exec/socket/*.cpp \
# 	srcs/exec/request/*.cpp \
#       srcs/exec/client/*.cpp \
#       srcs/exec/server/*.cpp \
# 	srcs/cgi/cgi.cpp

# FLAGS = -Wall -Wextra -Werror -std=c++98 -O3  -march=native -Ofast -funroll-loops -flto -fsanitize=address

# all: $(NAME)

# $(NAME):
# 	c++ $(FLAGS) $(SRC) -o $(NAME)

# # Build Docker image
# docker_build:
# 	docker build -t $(DOCKER_IMG_NAME) .

# # Create Docker network
# create_network:
# 	docker network create --driver bridge $(DOCKER_NETWORK_NAME) || true

# test-docker:
# 	@echo "Path: $$PATH"
# 	@which docker
# 	@docker --version

# # Run Docker container with the linked volume and custom network
# run: docker_build create_network
# 	docker run --rm -it --name $(DOCKER_CONTAINER_NAME) \
# 		--network $(DOCKER_NETWORK_NAME) \
# 		-p 8080-8090:8080-8090 \
# 		-v "$(PWD)/result.txt:/usr/src/app/result.txt" \
# 		$(DOCKER_IMG_NAME)

# # Stop Docker container
# stop:
# 	docker stop $(DOCKER_CONTAINER_NAME)

# clean:
# 	rm -rf $(NAME)

# fclean: clean

# # docker rm -f $(DOCKER_CONTAINER_NAME)
# # docker rmi $(DOCKER_IMG_NAME)
# # docker network rm $(DOCKER_NETWORK_NAME) || true

# re: fclean all

# .PHONY: all clean fclean re #docker_build run stop prog create_network


SRCS =		main.cpp \
			srcs/utils/utils.cpp \
			srcs/cgi/cgi.cpp \
			srcs/exec/server/serverExec.cpp \
			srcs/exec/server/Getter.cpp \
			srcs/exec/request/request.cpp \
			srcs/exec/request/reponse.cpp \
			srcs/exec/client/client.cpp \
			srcs/exec/socket/socket.cpp \
			srcs/parsing/server/server.cpp \
			srcs/parsing/verifyConfigFile.cpp \
			srcs/parsing/nginx/verifyServerContent.cpp \
			srcs/parsing/nginx/nginx.cpp \
			srcs/parsing/nginx/verifyParam.cpp \
			srcs/parsing/nginx/verifyLocationParams.cpp \
			srcs/parsing/nginx/verifFunction.cpp \
			srcs/parsing/nginx/verifyGenPartsOfServer.cpp \
			

NAME = Webserv
DOCKER_IMG_NAME = webserve_img
DOCKER_CONTAINER_NAME = webserve_container
DOCKER_NETWORK_NAME = webserve_network

OBJS	= ${SRCS:.cpp=.o}
INCS	= includes
CC		= c++
RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror -g -std=c++98

.cpp.o:
		${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o} -I ${INCS}

${NAME}: ${OBJS}
	${CC} ${OBJS} ${CFLAGS} -o ${NAME}

all: ${NAME}

# # Build Docker image
# docker_build:
# 	docker build -t $(DOCKER_IMG_NAME) .

# # Create Docker network
# create_network:
# 	docker network create --driver bridge $(DOCKER_NETWORK_NAME) || true

# test-docker:
# 	@echo "Path: $$PATH"
# 	@which docker
# 	@docker --version

# # Run Docker container with the linked volume and custom network
# run: docker_build create_network
# 	docker run --rm -it --name $(DOCKER_CONTAINER_NAME) \
# 		--network $(DOCKER_NETWORK_NAME) \
# 		-p 8080-8090:8080-8090 \
# 		-v "$(PWD)/result.txt:/usr/src/app/result.txt" \
# 		$(DOCKER_IMG_NAME)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

dfclean: fclean
			docker ${RM} $(DOCKER_CONTAINER_NAME)
			docker rmi $(DOCKER_IMG_NAME)
			docker network ${RM} $(DOCKER_NETWORK_NAME) || true

re: fclean all

dre: dfclean all

.PHONY: all clean fclean re dfclean

# make all: Compile et lance l'application dans Docker avec les configurations réseau spécifiées.
# make prog: Compile l'exécutable de l'application localement sans utiliser Docker.
# make docker_build: Construit l'image Docker basée sur le Dockerfile.
# make create_network: Crée un réseau Docker si ce n'est déjà fait.
# make test-docker: Affiche la version de Docker et le chemin actuel pour aider au dépannage.
# make run: Démarre le conteneur Docker en utilisant l'image construite et le réseau, mappe les ports spécifiés et monte le volume pour result.txt.
# make stop: Arrête le conteneur Docker actuellement en cours d'exécution.
# make clean: Supprime l'exécutable compilé localement.
# make fclean: Supprime l'exécutable, l'image Docker, le conteneur, et le réseau Docker.
# make re: Effectue un nettoyage complet puis recompile et redémarre l'application.