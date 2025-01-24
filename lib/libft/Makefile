# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 14:41:48 by lsasse            #+#    #+#              #
#    Updated: 2025/01/15 14:07:19 by pvasilan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## --- VARIABLES --- ##
SRC = atod atoi atol bzero calloc isalnum isalpha isascii isdigit isprint itoa \
	lstadd_back lstadd_front lstclear lstdelone lstiter lstlast lstmap lstnew \
	lstsize memchr memcmp memcpy memmove memset printf_utils printf putchar_fd \
	putendl_fd putnbr_fd putstr_fd split strcat strchr strcmp strcpy strcspn \
	strdup striteri strjoin strlcat strlcpy strlen strmapi strncmp strnstr \
	strspn strtok strtrim substr tolower toupper 
SRC := $(addprefix src/ft_, $(addsuffix .c, $(SRC)))
OBJS = ${SRC:%.c=%.o}

# Archive
NAME = libft.a

# Flags
CPPFLAGS = -I.
CFLAGS = -Wall -Wextra -Werror -g

# Shortcuts
RM = rm -f

## --- RULES --- ##
all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcs $@ $^

%.o: %.c
	@cc ${CPPFLAGS} $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re