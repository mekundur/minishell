# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 20:51:21 by lsasse            #+#    #+#              #
#    Updated: 2025/01/22 15:34:40 by pvasilan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## --- VARIABLES --- ##
# Utils source files
UTILS_SRC = 2d_str_utils errors execute_utils expand_vars fgets getenv has_flags \
	is_whitespace mem_utils parsing_utils quote_utils slice ft_gc exit_status \
	free_utils  token_utils expansion_utils expansion_utils2 \
	ft_remove_newline ft_remove_quotes ft_get_delim ft_heredoc_utils
UTILS_SRC := $(addprefix src/utils/, $(addsuffix .c, $(UTILS_SRC)))

# Builtins source files
CMD_SRC = cd.c echo.c env.c export.c unset.c exit.c pwd.c
CMD_SRC := $(addprefix src/commands/ft_, $(CMD_SRC))

# Minishell source files
SRC = main.c parsing.c signals.c constructors.c execute.c ft_pipe.c ft_redir.c \
	parsing_redir.c pars_redir_utils.c ft_heredoc.c 
SRC := $(addprefix src/, $(SRC))
SRC += $(CMD_SRC)
SRC += $(UTILS_SRC)

# Compiled objects
OBJS = ${SRC:%.c=%.o}

# Executables
NAME = minishell

# External libraries
LIBFT = lib/libft
READLINE = /usr/local/opt/readline

# Flags
CPPFLAGS = -I./include/ -I$(READLINE)/include
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L./$(LIBFT) -lft -L$(READLINE)/lib -lreadline

# Shortcuts
RM = rm -f

## --- RULES --- ##
all	: __lib $(NAME)

# Make external libraries
__lib:
	make -sC $(LIBFT)

# Make executables
$(NAME): $(OBJS)
	cc $^ $(LDFLAGS) -o $@ -lreadline

%.o: %.c
	cc $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Manage object files and executables
clean :
	make clean -sC $(LIBFT)
	$(RM) $(OBJS)
	
fclean:
	make fclean -sC $(LIBFT)
	$(RM) $(OBJS) $(NAME)

re : fclean all

# Test pipelines
testing	:
	@clear
	@echo "Removing old files ..."
	@make fclean
	@clear
	@echo "Compiling minishell ..."
	@make
	@clear
	@make clean
	@clear
	@echo  "Starting minishell ...\n\n"
	@./minishell

valtest	:
	@clear
	@echo "Removing old files ..."
	@make fclean
	@clear
	@echo "Compiling minishell ..."
	@make
	@clear
	@make clean
	@clear
	@echo  "Starting minishell ...\n\n"
	@valgrind --leak-check=full --track-origins=yes ./minishell

valtestfull :
	@clear
	@echo "Removing old files ..."
	@make fclean
	@clear
	@echo "Compiling minishell ..."
	@make
	@clear
	@make clean
	@clear
	@echo  "Starting minishell ...\n\n"
	@valgrind --leak-check=full --show-leak-kinds=all ./minishell
