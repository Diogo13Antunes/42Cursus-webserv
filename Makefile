NAME = webserv

CXX = c++
# CXXFLAGS = -Wall -Werror -Wextra -g -fsanitize=address -std=c++98
CXXFLAGS = -g -std=c++98
RM = rm -f

#$(VERBOSE).SILENT:

INC = -I ./includes

SRC_PATH = ./sources

OBJ_PATH = ./objects

SRC_NAME =	main.cpp				\
			Connection.cpp			\
			Connections.cpp			\
			EventLoop.cpp			\
			WriteHandler.cpp		\
			ReadHandler.cpp			\
			EventHandlerFactory.cpp	\

OBJS = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.cpp=.o))

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

all: $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(INC) -o $(NAME)
	@echo "\033[1;36m[COMPILED]\033[0m"

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.cpp
	mkdir -p objects
	$(CXX) -c $(CXXFLAGS) $(INC) $< -o $@

clean:
	rm -rf $(OBJ_PATH)
	@echo "\033[1;33mAll $(NAME).o files are removed\033[0m"

fclean: clean
	rm -f $(NAME)
	@echo "\033[1;31m$(NAME) is deleted\033[0m"

re: fclean all

.PHONY: all clean fclean re
