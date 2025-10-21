# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 15:48:21 by cczerwin          #+#    #+#              #
#    Updated: 2024/10/30 15:48:24 by cczerwin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -c
#C_FILES	:=	$(wildcard *.c)

FT_PRINT 	:= 	src/ft_printf/ft_parsing.c						\
				src/ft_printf/ft_padding.c						\
				src/ft_printf/ft_printcs.c						\
				src/ft_printf/ft_printdi.c						\
				src/ft_printf/ft_printf.c						\
				src/ft_printf/ft_printp.c						\
				src/ft_printf/ft_printu.c						\
				src/ft_printf/ft_printx.c						\

GNL			:= 	src/gnl/get_next_line_bonus.c					\
				src/gnl/get_next_line_utils_bonus.c				\
				src/gnl/get_next_line.c							\

LIST		:=	src/list/ft_lstadd_front.c						\
				src/list/ft_lstadd_back.c						\
				src/list/ft_lstclear.c							\
				src/list/ft_lstdelone.c							\
				src/list/ft_lstiter.c							\
				src/list/ft_lstlast.c							\
				src/list/ft_lstmap.c							\
				src/list/ft_lstnew.c							\
				src/list/ft_lstsize.c							\

MATH		:=	src/math/abs_val.c								\
				src/math/ft_fibonacci.c							\
				src/math/ft_next_prime.c						\
				src/math/ft_rec_factorial.c						\
				src/math/ft_sqrt.c								\
				src/math/ft_util_pow.c							\

MEM			:=	src/mem/ft_bzero.c								\
				src/mem/ft_calloc.c								\
				src/mem/ft_memchr.c								\
				src/mem/ft_memcmp.c								\
				src/mem/ft_memcpy.c								\
				src/mem/ft_memmove.c							\
				src/mem/ft_memset.c								\

MISC		:=	src/misc/ft_atoi.c								\
				src/misc/ft_intchr.c							\
				src/misc/ft_itoa.c								\
				src/misc/ft_long_atoi.c							\
				src/misc/ft_putchar_fd.c						\
				src/misc/ft_putstr_fd.c							\
				src/misc/ft_putendl_fd.c						\
				src/misc/ft_putnbr_fd.c							\
				src/misc/ft_range.c								\
				src/misc/ft_tolower.c							\
				src/misc/ft_toupper.c							\

STR			:=	src/str/ft_int_strlen.c							\
				src/str/ft_split.c								\
				src/str/ft_strchr.c								\
				src/str/ft_strdup.c								\
				src/str/ft_striteri.c							\
				src/str/ft_strjoin.c							\
				src/str/ft_strlcat.c							\
				src/str/ft_strlcpy.c							\
				src/str/ft_strlen.c								\
				src/str/ft_strmapi.c							\
				src/str/ft_strncmp.c							\
				src/str/ft_strnstr.c							\
				src/str/ft_strrchr.c							\
				src/str/ft_strtrim.c							\
				src/str/ft_substr.c								\
				

TYPE		:=	src/type/ft_isalnum.c							\
				src/type/ft_isalpha.c							\
				src/type/ft_isascii.c							\
				src/type/ft_isdigit.c							\
				src/type/ft_isprint.c							\
				src/type/ft_isset.c								\

LIBFT		:=	$(LIST) $(MATH) $(MEM) $(MISC) $(STR) $(TYPE)
C_FILES		:= 	$(FT_PRINT) $(GNL) $(LIBFT)

OBJ			:=	$(C_FILES:.c=.o)
NAME		:=	libft.a
INCLUDE		:=	-I./includes

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rcs $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) $< -o $@
	
clean:
	@rm -f $(OBJ) $(OBJ_B)
	
fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
