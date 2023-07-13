NAME = webserv

CXX = c++
# CXXFLAGS = -Wall -Werror -Wextra -g -fsanitize=address -std=c++98
CXXFLAGS = -g -std=c++98 -march=native -fsanitize=address
RM = rm -f

$(VERBOSE).SILENT:

INC =	-I ./sources -I ./sources/connections -I ./sources/messenger -I ./sources/eventloop -I ./sources/configs -I ./sources/request -I ./sources/handleReq -I ./sources/handleCgi -I ./sources/request -I ./sources/handleRes -I ./sources/errorPageBuilder -I ./sources/CGIExecuter -I ./sources/httpHeaderBuilder -I ./sources/utils

SRC_PATH = ./sources

OBJ_PATH = ./objects

SRC_NAME =	main.cpp								\
			connections/Connection.cpp				\
			connections/Connections.cpp				\
			messenger/AMessengerClient.cpp			\
			messenger/Messenger.cpp					\
			messenger/Message.cpp					\
			messenger/ConnectionMessage.cpp			\
			messenger/EventMessage.cpp				\
			eventloop/EventLoop.cpp					\
			eventloop/WriteHandler.cpp				\
			eventloop/ReadHandler.cpp				\
			eventloop/CGIHandler.cpp				\
			eventloop/EventHandlerFactory.cpp		\
			eventloop/Event.cpp						\
			eventloop/EventDemux.cpp				\
			configs/Configs.cpp						\
			configs/ConfigsUtils.cpp				\
			configs/ConfigsData.cpp					\
			request/RequestParser.cpp				\
			request/RequestParserUtils.cpp			\
			request/RequestData.cpp					\
			request/RequestDataUtils.cpp			\
			handleReq/HandleReq.cpp					\
			handleReq/HeaderProcess.cpp				\
			handleReq/BodyProcess.cpp				\
			handleRes/HandleRes.cpp					\
			handleRes/CreateHeaderState.cpp			\
			handleRes/GetBodyState.cpp				\
			handleRes/ResponseState.cpp				\
			handleCgi/HandleCgi.cpp					\
			handleCgi/ExecCgiState.cpp				\
			handleCgi/GettingDataCgiState.cpp		\
			CGIExecuter/CGIExecuter.cpp				\
			errorPageBuilder/ErrorPageBuilder.cpp	\
			httpHeaderBuilder/HttpHeaderBuilder.cpp	\
			utils/TimeDate.cpp						\
			utils/Timer.cpp							\
			Terminal.cpp

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
	mkdir -p objects/configs
	mkdir -p objects/request
	mkdir -p objects/handleReq
	mkdir -p objects/handleRes
	mkdir -p objects/handleCgi
	mkdir -p objects/errorPageBuilder
	mkdir -p objects/httpHeaderBuilder
	mkdir -p objects/CGIExecuter
	mkdir -p objects/utils
	$(CXX) -c $(CXXFLAGS) $(INC) $< -o $@

clean:
	rm -rf $(OBJ_PATH)
	@echo "\033[1;33mAll $(NAME).o files are removed\033[0m"

fclean: clean
	rm -f $(NAME)
	@echo "\033[1;31m$(NAME) is deleted\033[0m"

re: fclean all

.PHONY: all clean fclean re
