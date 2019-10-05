# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/21 01:42:45 by aait-ihi          #+#    #+#              #
#    Updated: 2019/10/04 17:40:31 by aait-ihi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


FT_LS = ft_ls

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC =	ft_ls.c\
		collect_data.c\
		get_data.c\
		display_data.c\
		merge_sort.c\
		print_function.c\
		allocat_free_memory.c\
		helper.c\
		print_colors.c

LIB_FT = libft/libft.a

OBJ = $(SRC:%c=%o)

all : $(FT_LS)


$(LIB_FT) : lib

lib:
	make -C libft

$(FT_LS) :$(LIB_FT) $(OBJ)  ft_ls.h
	$(CC) -g -o $(FT_LS) $(CFLAGS) $(SRC) $(LIB_FT)

clean :
	make clean -C libft
	/bin/rm -rf $(OBJ)

fclean : clean
	make fclean -C libft
	/bin/rm -rf $(FT_LS)

re_$(FT_LS) : 
	/bin/rm -rf $(OBJ)
	make all

re : fclean all
