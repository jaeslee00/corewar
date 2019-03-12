# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 17:52:11 by jaelee            #+#    #+#              #
#    Updated: 2019/03/12 14:21:59 by jaelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm
SRCS = main.c \
		read_file.c \
		op.c \
		error.c
INCLUDES = ./includes/assembler.h \
			./includes/op.h \
			./libft/includes/libft.h
OBJS = $(patsubst %.c,obj/%.o,$(SRCS))
CC = gcc
CFLAGS := $(FLAGS) -Wall -Wextra -Werror
INCLUDE_FOLDERS = -I./includes -I./libft/includes
LIBRARY_PATH = -Llibft

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) $(LIBRARY_PATH) -lft $(OBJS) -o $@

obj:
	mkdir -p obj

obj/%.o: src/%.c $(INCLUDES) | obj
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) -c $< -o $@

libft/libft.a: libft/includes/libft.h
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJS)
	rm -rf obj
	rm -rf asm.dSYM

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean
	make all
