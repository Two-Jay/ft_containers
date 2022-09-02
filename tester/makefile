NAME = container_tester

SRCS_PATH		= .
INCS_PATH		= ./includes

SRCS			= $(SRCS_PATH)/main.cpp
OBJS			= $(SRCS:.cpp=.o)

CXX				= clang++
CXXFLAGS		= -Wall -Werror -Wextra -std=c++98 -g3
# CXXFLAGS		= -std=c++98 -fsanitize=address

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) -I $(INCS_PATH) -o $(NAME) $(OBJS)

clean:
				rm -f $(OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re