NAME = webserv

CXX = c++
# CXXFLAGS = -Wall -Werror -Wextra -g -fsanitize=address -std=c++98
CXXFLAGS = -std=c++98 -g -fsanitize=address
RM = rm -f

$(VERBOSE).SILENT:

INC = -I ./sources -I ./sources/configs -I ./sources/request -I ./includes

SRC_PATH = ./sources

OBJ_PATH = ./objects

SRC_NAME =	main.cpp							\
			configs/Configs.cpp					\
			configs/ConfigsUtils.cpp			\
			configs/ConfigsData.cpp				\
			request/RequestParser.cpp			\
			request/RequestParserUtils.cpp		\
			request/RequestData.cpp				\
			request/RequestDataUtils.cpp		\
			Terminal.cpp

OBJS = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.cpp=.o))

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

all: $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(INC) -o $(NAME)
	@echo "\033[1;36m[COMPILED]\033[0m"

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.cpp
	mkdir -p objects
	mkdir -p objects/configs
	mkdir -p objects/request
	$(CXX) -c $(CXXFLAGS) $(INC) $< -o $@

clean:
	rm -rf $(OBJ_PATH)
	@echo "\033[1;33mAll $(NAME).o files are removed\033[0m"

fclean: clean
	rm -f $(NAME)
	@echo "\033[1;31m$(NAME) is deleted\033[0m"

re: fclean all

.PHONY: all clean fclean re
