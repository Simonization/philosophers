# Philosophers Makefile

NAME		= philo

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
RM			= rm -f

# Directories
SRCS_DIR	= src/
INCS_DIR	= includes/
OBJS_DIR	= objs/

# Source files
SRCS		= main.c init.c utils.c time.c philosopher.c actions.c monitor.c
SRCS_PREFIXED = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS		= $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

# Includes
INCLUDES	= -I $(INCS_DIR)

# Colors for output
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RESET		= \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) -r $(OBJS_DIR)
	@echo "$(YELLOW)Object files removed!$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)$(NAME) removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re