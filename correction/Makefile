# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/22 17:11:22 by lgarczyn          #+#    #+#              #
#    Updated: 2018/01/26 00:20:12 by lgarczyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nm_otool

SRC = main.c array.c sorted.c queue.c bitmap.c

INC = -Ilibft/includes -Iprintf/includes
		
OBJ = $(addprefix obj/, $(addsuffix .o, $(basename $(SRC))))

LIB = -L libft -lft -L printf -lftprintf

DEB = -g -g3 -fsanitize=address 

OPT = -O0 #-O3

FLG = -Wall -Wextra -funsigned-char -fno-signed-char -m64 $(OPT) $(DEB) -std=c11

all: $(NAME)

$(NAME):$(OBJ)
	cd libft && make
	cd printf && make
	gcc -o ft_data $(OBJ) $(INC) $(FLG) $(LIB)
	
obj/%.o: src/%.c
	@mkdir -p obj
	gcc  -o $@ -c $< $(INC) $(FLG)

lib:
	rm -rf $(OBJ)
	rm -f ft_nm ft_otool
	rm -rf *.dSYM

clean:
	rm -rf $(OBJ)
	cd libft && make clean
	cd printf && make clean

fclean: lib
	rm -f ft_nm ft_otool
	rm -rf *.dSYM
	cd libft && make fclean
	cd printf && make fclean

re: fclean all

libre: lib all

optire: fclean opti