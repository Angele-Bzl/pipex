# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 16:11:34 by abarzila          #+#    #+#              #
#    Updated: 2025/03/17 13:58:51 by abarzila         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re lib bonus
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
DLIBFT			=	libft
DSRC			=	src
DOBJ			=	obj
DHEADER			=	header

#####################################################
#					FLAGS							#
#####################################################
CFLAGS		=	-Wall -Wextra -Werror -g3 -g

#####################################################
#					FILES							#
#####################################################
CFILES		=	main.c\
				utils.c\
				command.c

CHEADERS	=	pipex.h
SRC			=	$(DSRC)/$(CFILES)
HEADERS		=	$(DHEADER)/$(CHEADERS)
OBJ			=	$(CFILES:%.c=$(DOBJ)/%.o)

#####################################################
#					BONUS							#
#####################################################
DSRC_BONUS		=	src_bonus
DOBJ_BONUS		=	obj_bonus
DHEADER_BONUS	=	header_bonus

CFILES_BONUS	=	main_bonus.c\
					utils_bonus.c\
					command_bonus.c

CHEADERS_BONUS	=	pipex_bonus.h
SRC_BONUS		=	$(DSRC_BONUS)/$(CFILES_BONUS)
HEADERS_BONUS	=	$(DHEADER_BONUS)/$(CHEADERS_BONUS)
OBJ_BONUS		=	$(CFILES_BONUS:%.c=$(DOBJ_BONUS)/%.o)

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

#bonus##############

bonus : lib $(OBJ_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) -o $(NAME)

$(DOBJ_BONUS)/%.o : $(DSRC_BONUS)/%.c $(HEADERS_BONUS) Makefile | $(DOBJ_BONUS)
	$(CC) $(CFLAGS) -o $@ -c $<

$(DOBJ_BONUS) :
	mkdir -p $(DOBJ_BONUS)

####################

re: fclean
	$(MAKE) all

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(DLIBFT)/

clean :
	rm -rf $(DOBJ)
	rm -rf $(DOBJ_BONUS)
	$(MAKE) clean -C $(DLIBFT)/
