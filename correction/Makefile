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

NAME = ft_data

SRC = main.c

INC = -Ilibft/includes -Iprintf/includes -Idata/includes
		
OBJ = $(addprefix obj/, $(addsuffix .o, $(basename $(SRC))))

LIB = -L libft -lft -L printf -lftprintf -L data -lftdata

DEB = -g -g3 #-fsanitize=address 

OPT = #-O3

FLG = -Wall -Wextra -funsigned-char -fno-signed-char -m64 $(OPT) $(DEB) -std=c11

all: $(NAME)

$(NAME):$(OBJ) libft/libft.a printf/libprintf.a data/libdata.a
	gcc -o ft_data $(OBJ) $(INC) $(FLG) $(LIB)
	
obj/%.o: src/%.c
	@mkdir -p obj
	gcc  -o $@ -c $< $(INC) $(FLG)

%.a:
	cd `dirname $@` && make

lib:
	@rm -rf $(OBJ)
	@rm -f ft_data
	@rm -rf *.dSYM

clean:
	@rm -f $(OBJ)
	cd libft && make clean
	cd printf && make clean
	cd data && make clean

fclean: lib
	@rm -f ft_data
	@rm -rf *.dSYM
	cd libft && make fclean
	cd printf && make fclean
	cd data && make fclean

re: fclean all

libre: lib all

optire: fclean opti
