# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 16:11:34 by abarzila          #+#    #+#              #
#    Updated: 2025/02/18 17:25:42 by abarzila         ###   ########.fr        #
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

#####################################################
#					FLAGS							#
#####################################################
CFLAGS		=	-Wall -Wextra -Werror

#####################################################
#					FILES							#
#####################################################
CFILES			=	main.c\
					utils.c\
					parent.c\
					child.c

HEADERS		=	pipex.h
SRC			=	$(DSRC)/$(CFILES)
OBJ			=	$(CFILES:%.c=$(DOBJ)/%.o)

#####################################################
#					ARCHIVES						#
#####################################################
AR			=	ar
AFLAG		=	rcs
LIBFT		=	libft/libft.a

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
