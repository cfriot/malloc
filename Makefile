# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdurand <tdurand@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 17:26:08 by tdurand           #+#    #+#              #
#    Updated: 2015/03/23 19:07:12 by cfriot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

LIB = libft/libft.a

CFLAGS = -Wall -Wextra -Werror

SRC = ft_malloc.c \
	  ft_destroy.c \
	  ft_malloc_tools_tiny.c \
	  ft_malloc_tools_small.c \
	  ft_malloc_tools_large.c \
	  ft_ini_env.c \
	  ft_display_malloc.c \
	  ft_realloc.c \
	  ft_realloc2.c \
	  ft_search.c \
	  ft_show_mem.c

OBJ = $(SRC:.c=.o)

.PHONY: all libft clean fclean re

all : libft $(NAME)

$(NAME):  $(OBJ)
	@$(CC) -shared -o $(NAME) $(OBJ) $(LIB)
	@ln -s $(NAME) libft_malloc.so
	@echo "!"
	@echo "$(NAME) compiled\033[0m"

libft :
	@make -C libft/

%.o : %.c
	@$(CC) -c $(CFLAGS) -I./includes/ -I./libft/includes $<
	@printf "\033[32m."

clean :
	@make -C libft/ clean
	@/bin/rm -f $(OBJ)
	@echo "\033[31m$(NAME) objects deleted\033[0m"

fclean : allclean
	@/bin/rm -f $(NAME)
	@echo "\033[31m$(NAME) deleted\033[0m"

allclean :
	@make -C libft/ fclean
	@/bin/rm -f libft_malloc.so
	@/bin/rm -f $(OBJ)
	@echo "\033[31m$(NAME) objects deleted\033[0m"

re : fclean all
