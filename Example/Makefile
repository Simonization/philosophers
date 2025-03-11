# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugerkens <ugerkens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 15:29:43 by ugerkens          #+#    #+#              #
#    Updated: 2024/04/18 12:45:58 by ugerkens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -O3 -MMD -MP -pthread
NAME			=	philo

# Include directories
INC_DIRS		=	include src
CFLAGS			+=	$(addprefix -I, $(INC_DIRS))

# Source and Object Files
VPATH			=	src src/utils
SRC				=	main.c arguments.c \
					init_simulation.c simulation.c \
					philo_routine.c philo_actions.c \
					monitor.c logger.c time.c \
					error.c list.c allocation.c
OBJ			 	=	$(SRC:%.c=build/%.o)
DEP			 	=	$(OBJ:%.o=%.d)
OBJ_DIR_NAME	=	build

# Rules
all:			$(NAME)

$(NAME):		$(OBJ_DIR_NAME) $(OBJ)
				$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ_DIR_NAME):
				mkdir -p $(OBJ_DIR_NAME)

build/%.o:		%.c
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				rm -rf build

fclean:			clean
				rm -rf $(NAME)

re:			 	fclean all

-include $(DEP)

.PHONY:		 all clean fclean re

.SILENT:
