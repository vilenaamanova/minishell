# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 11:54:04 by ncathy            #+#    #+#              #
#    Updated: 2022/09/10 13:26:36 by ncathy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCS	=	ft_atoi.c		ft_bzero.c		ft_isalnum.c\
			ft_isalpha.c	ft_isascii.c	ft_isdigit.c\
			ft_isprint.c	ft_memchr.c		ft_memcmp.c\
			ft_memset.c		ft_memcpy.c		ft_strlcpy.c\
			ft_strchr.c		ft_strncmp.c	ft_memmove.c\
			ft_strlen.c		ft_strlcat.c	ft_strrchr.c\
			ft_tolower.c	ft_toupper.c	ft_strnstr.c\
			ft_strdup.c		ft_calloc.c		ft_substr.c\
			ft_strjoin.c	ft_striteri.c	ft_strmapi.c\
			ft_putchar_fd.c	ft_putstr_fd.c	ft_putendl_fd.c\
			ft_putnbr_fd.c	ft_strtrim.c	ft_itoa.c\
			ft_split.c		ft_isspace.c\

SRCS_BONUS	=	ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c \
				ft_lstlast.c	ft_lstadd_back.c	ft_lstdelone.c \
				ft_lstclear.c	ft_lstiter.c		ft_lstmap.c \

HEADER	=	libft.h

OBJ		=	$(patsubst %.c, %.o, $(SRCS))

OBJ_BONUS	=	$(OBJ) $(patsubst %.c, %.o, $(SRCS_BONUS))

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

.PHONY	:	all bonus clean fclean re

all 	:	$(NAME)

bonus	:	$(OBJ_BONUS) $(HEADER)
	ar rcs $(NAME) $?

$(NAME)	:	$(OBJ_BONUS) $(HEADER)
	ar rcs $(NAME) $?

%.o	: %.c	$(HEADER)
	$(CC)	$(CFLAGS) -c $< -o $@

clean	:
	@rm -f $(OBJ)
	@rm -f $(OBJ_BONUS)

fclean	:	clean
	@$(RM) $(NAME)

re		:	fclean all
