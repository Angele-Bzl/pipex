# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 16:11:34 by abarzila          #+#    #+#              #
#    Updated: 2025/03/03 11:19:13 by abarzila         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re lib
#####################################################
#					PROGRAM							#
#####################################################
NAME		=	pipex

#####################################################
#					COMPILING						#
#####################################################
CC			=	cc

#####################################################
#					DIRECTORY						#
#####################################################
DLIBFT		=	libft
DSRC		=	src
DOBJ		=	obj
DHEADER		=	header

#####################################################
#					FLAGS							#
#####################################################
CFLAGS		=	-Wall -Wextra -Werror

#####################################################
#					FILES							#
#####################################################
CFILES		=	main.c\
				utils.c\
				first_child.c\
				last_child.c

CHEADERS	=	pipex.h
SRC			=	$(DSRC)/$(CFILES)
HEADERS		=	$(DHEADER)/$(CHEADERS)
OBJ			=	$(CFILES:%.c=$(DOBJ)/%.o)

#####################################################
#					ARCHIVES						#
#####################################################
LIBFT		=	libft/libft.a\
				libft/printf/libftprintf.a\
				libft/printf_err/libftprintf.a\

all : lib
	$(MAKE) $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(DOBJ)/%.o : $(DSRC)/%.c $(HEADERS) Makefile | $(DOBJ)
	$(CC) $(CFLAGS) -o $@ -c $<

$(DOBJ):
	mkdir -p $(DOBJ)

lib :
	$(MAKE) -C $(DLIBFT)/

re: fclean
	$(MAKE) all

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(DLIBFT)/

clean :
	rm -rf $(DOBJ)
	$(MAKE) clean -C $(DLIBFT)/
