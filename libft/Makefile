# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 13:44:29 by abarzila          #+#    #+#              #
#    Updated: 2025/01/20 16:32:26 by abarzila         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
CC	=	cc
CFLAG	=	-Wall -Wextra -Werror
INC		=	libft.h\
			get_next_line.h

OBJ	=	$(SRC:.c=.o)
OBJ_BONUS	=	$(BONUS:.c=.o)
SRC	=	ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_strlen.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_memchr.c\
		ft_atoi.c\
		ft_memcmp.c\
		ft_strnstr.c\
		ft_strdup.c\
		ft_strncmp.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_split.c\
		ft_strtrim.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_itoa.c\
		ft_calloc.c\
		get_next_line.c\
		get_next_line_utils.c

BONUS = ft_lstnew_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c\
		ft_lstiter_bonus.c\
		ft_lstmap_bonus.c

all: $(NAME)

.bonus: $(OBJ) $(OBJ_BONUS)
	ar rcs $(NAME) $(OBJ) $(OBJ_BONUS)
	touch .bonus

bonus: .bonus

$(NAME): $(OBJ) $(INC) Makefile
	ar rcs $(NAME) $(OBJ)

%.o: %.c $(INC)
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS) .bonus

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
