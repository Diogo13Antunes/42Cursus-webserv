NAME = webserv

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -g -fsanitize=address -std=c++98
#CXXFLAGS = -g -std=c++98 -march=native -fsanitize=address
# CXXFLAGS = -g -std=c++98 -march=native
RM = rm -f

$(VERBOSE).SILENT:

INC := $(addprefix -I, $(shell find sources -type d))

SRC_PATH = ./sources

OBJ_PATH = ./objects

#SRC_NAME =	main.cpp								\
			connections/Connection.cpp				\
			connections/Connections.cpp				\
			messenger/AMessengerClient.cpp			\
			messenger/Messenger.cpp					\
			messenger/Message.cpp					\
			eventloop/EventLoop.cpp					\
			eventloop/WriteHandler.cpp				\
			eventloop/ReadHandler.cpp				\
			eventloop/WriteCgiHandler.cpp			\
			eventloop/ReadCgiHandler.cpp			\
			eventloop/CGIHandler.cpp				\
			eventloop/TypeTransitionHandler.cpp		\
			eventloop/EventHandlerFactory.cpp		\
			eventloop/Event.cpp						\
			eventdemux/EventDemux.cpp				\
			configs/Configs.cpp						\
			configs/ConfigsUtils.cpp				\
			configs/ConfigsData.cpp					\
			request/RequestParser.cpp				\
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
			utils/StringUtils.cpp					\
			utils/TimeDate.cpp						\
			utils/Timer.cpp							\
			Terminal.cpp

SRC_NAME = $(shell find $(SRC_PATH) -type f -name "*.cpp" -printf "%P " -o -type f -name "*.cpp" -printf "%f ")

OBJS = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.cpp=.o))

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

SRC_DIRS = $(sort $(dir $(SRC_NAME)))

all: $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(INC) -o $(NAME)
	@echo "\033[1;36m[COMPILED]\033[0m"

# $(OBJ_PATH)/%.o : $(SRC_PATH)/%.cpp
# 	mkdir -p objects
# 	mkdir -p objects/connections
# 	mkdir -p objects/messenger
# 	mkdir -p objects/eventloop
# 	mkdir -p objects/configs
# 	mkdir -p objects/request
# 	mkdir -p objects/handleReq
# 	mkdir -p objects/handleRes
# 	mkdir -p objects/handleCgi
# 	mkdir -p objects/errorPageBuilder
# 	mkdir -p objects/httpHeaderBuilder
# 	mkdir -p objects/CGIExecuter
# 	mkdir -p objects/utils
# 	mkdir -p objects/eventdemux
# 	$(CXX) -c $(CXXFLAGS) $(INC) $< -o $@

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.cpp
	$(shell mkdir -p $(addprefix $(OBJ_PATH)/, $(SRC_DIRS)))
	$(CXX) -c $(CXXFLAGS) $(INC) $< -o $@

clean:
	rm -rf $(OBJ_PATH)
	@echo "\033[1;33mAll $(NAME).o files are removed\033[0m"

fclean: clean
	rm -f $(NAME)
	@echo "\033[1;31m$(NAME) is deleted\033[0m"

re: fclean all

.PHONY: all clean fclean re
