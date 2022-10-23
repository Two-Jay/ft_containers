NAME		=	containers_test

CXX			=	c++
CXXFLAG		=	-Wall -Wextra -Werror -std=c++98
G			=	-g3
INCLUDE		=	-I$(INC_DIR) -I$(LIBFT_DIR) $(CPPFLAGS)

OBJ_DIR		=	./obj/
SRC_DIR		=	./test/
INC_DIR		=	./test/

SRC_FILE		=	main.cpp \
					test_rbt.cpp \
					test_vector.cpp \
					test_stack.cpp \
					test_map.cpp \
					test_set.cpp \
					test_utils.cpp

MAIN_OBJ_FILE	=	$(SRC_FILE:.cpp=.o)

MAIN_OBJ		=	$(addprefix $(OBJ_DIR), $(MAIN_OBJ_FILE))

OBJ				= 	$(MAIN_OBJ)

all			:	$(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(G) $(CXXFLAG) $(INCLUDE) $< -c -o $@

$(NAME)		:	$(OBJ)
	@$(CXX) $(G) $(CXXFLAG) $(OBJ) $(INCLUDE) -o $@
	@echo "\033[0;92m* $(NAME) program file was created *\033[0m"

clean		:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;91m* $(NAME)'s object files were removed* \033[0m"

fclean		:	clean
	@rm -f $(NAME)
	@echo "\033[0;91m* $(NAME) were removed* \033[0m"

re			:	fclean all

.PHONY: all, clean, fclean, re