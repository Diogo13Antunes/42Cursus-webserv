NAME = webserv

CXX = c++
# CXXFLAGS = -Wall -Werror -Wextra -g -fsanitize=address -std=c++98
CXXFLAGS = -g -std=c++98
RM = rm -f

#$(VERBOSE).SILENT:

INC = -I ./sources -I ./sources/connections -I ./sources/messenger -I ./sources/eventloop

SRC_PATH = ./sources

OBJ_PATH = ./objects

SRC_NAME =	main.cpp							\
			connections/Connection.cpp			\
			connections/Connections.cpp			\
			messenger/AMessengerClient.cpp		\
			messenger/Messenger.cpp				\
			messenger/Message.cpp				\
			messenger/ConnectionMessage.cpp		\
			messenger/EventMessage.cpp			\
			eventloop/EventLoop.cpp				\
			eventloop/WriteHandler.cpp			\
			eventloop/ReadHandler.cpp			\
			eventloop/EventHandlerFactory.cpp	\
			eventloop/Event.cpp					\
			eventloop/EventDemux.cpp			\


OBJS = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.cpp=.o))

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

all: $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(INC) -o $(NAME)
	@echo "\033[1;36m[COMPILED]\033[0m"

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.cpp
	mkdir -p objects
	mkdir -p objects/connections
	mkdir -p objects/messenger
	mkdir -p objects/eventloop
	$(CXX) -c $(CXXFLAGS) $(INC) $< -o $@

clean:
	rm -rf $(OBJ_PATH)
	@echo "\033[1;33mAll $(NAME).o files are removed\033[0m"

fclean: clean
	rm -f $(NAME)
	@echo "\033[1;31m$(NAME) is deleted\033[0m"

re: fclean all

.PHONY: all clean fclean re
