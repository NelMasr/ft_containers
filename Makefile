NAME1	=	ft_vector
NAME2	=	ft_map
NAME3	=	ft_stack

NAME4	=	std_vector
NAME5	=	std_map
NAME6	=	std_stack

SRCS1	=	mains/main_vector_ft.cpp
SRCS2	=	mains/main_map_ft.cpp
SRCS3	=	mains/main_stack_ft.cpp

SRCS4	=	mains/main_vector_std.cpp
SRCS5	=	mains/main_map_std.cpp
SRCS6	=	mains/main_stack_std.cpp

SRCS7	=	mains/main.cpp

OBJS1	=	${SRCS1:.cpp=.o}
OBJS2	=	${SRCS2:.cpp=.o}
OBJS3	=	${SRCS3:.cpp=.o}

OBJS4	=	${SRCS4:.cpp=.o}
OBJS5	=	${SRCS5:.cpp=.o}
OBJS6	=	${SRCS6:.cpp=.o}

# COLORS
C_DEF	=	"\033[00m"
C_OK	=	"\033[36m"
C_GOOD	=	"\033[32m"
C_ERROR	=	"\033[31m"
C_WARN	=	"\033[33m"
C_PGM	=	"\033[34m"

# DBG MESSAGE
SUCCESS	=	$(C_GOOD)SUCCESS !$(C_DEF)
OK		=	$(C_OK)OK$(C_DEF)

CC		=	c++
CFLAGS	=	-Wall -Wextra -Werror -g -std=c++98

.cpp.o:
			${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o}

all:
			@$(MAKE) -j $(NAME1)
			@$(MAKE) -j $(NAME2)
			@$(MAKE) -j $(NAME3)
			@$(MAKE) -j $(NAME4)
			@$(MAKE) -j $(NAME5)
			@$(MAKE) -j $(NAME6)

vector:
			@$(MAKE) -j $(NAME1)
			@$(MAKE) -j $(NAME4)

map:
			@$(MAKE) -j $(NAME2)
			@$(MAKE) -j $(NAME5)

stack:
			@$(MAKE) -j $(NAME3)
			@$(MAKE) -j $(NAME6)

$(NAME1):	$(OBJS1)
			${CC} $(CFLAGS) -o $(NAME1) $(OBJS1)
			@echo "Creating [ \e[1;34m$(NAME1)\e[0m ]" $(SUCCESS)

$(NAME2):	$(OBJS2)
			${CC} $(CFLAGS) -o $(NAME2) $(OBJS2)
			@echo "Creating [ \e[1;34m$(NAME2)\e[0m ]" $(SUCCESS)

$(NAME3):	$(OBJS3)
			${CC} $(CFLAGS) -o $(NAME3) $(OBJS3)
			@echo "Creating [ \e[1;34m$(NAME3)\e[0m ]" $(SUCCESS)

$(NAME4):	$(OBJS4)
			${CC} $(CFLAGS) -o $(NAME4) $(OBJS4)
			@echo "Creating [ \e[1;34m$(NAME4)\e[0m ]" $(SUCCESS)

$(NAME5):	$(OBJS5)
			${CC} $(CFLAGS) -o $(NAME5) $(OBJS5)
			@echo "Creating [ \e[1;34m$(NAME5)\e[0m ]" $(SUCCESS)

$(NAME6):	$(OBJS6)
			${CC} $(CFLAGS) -o $(NAME6) $(OBJS6)
			@echo "Creating [ \e[1;34m$(NAME6)\e[0m ]" $(SUCCESS)

clean:
			@rm -rf $(OBJS1)
			@rm -rf $(OBJS2)
			@rm -rf $(OBJS3)
			@rm -rf $(OBJS4)
			@rm -rf $(OBJS5)
			@rm -rf $(OBJS6)
			@echo "Cleaning the .o mess..." $(OK)

fclean:		clean
			@rm -rf $(NAME1)
			@rm -rf $(NAME2)
			@rm -rf $(NAME3)
			@rm -rf $(NAME4)
			@rm -rf $(NAME5)
			@rm -rf $(NAME6)
			@echo "Deleting [ \e[1;34m$(NAME1)\e[0m ]" $(OK)
			@echo "Deleting [ \e[1;34m$(NAME2)\e[0m ]" $(OK)
			@echo "Deleting [ \e[1;34m$(NAME3)\e[0m ]" $(OK)
			@echo "Deleting [ \e[1;34m$(NAME4)\e[0m ]" $(OK)
			@echo "Deleting [ \e[1;34m$(NAME5)\e[0m ]" $(OK)
			@echo "Deleting [ \e[1;34m$(NAME6)\e[0m ]" $(OK)

re:			fclean all

.PHONY:		all clean fclean re
