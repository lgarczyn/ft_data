# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/22 17:11:22 by lgarczyn          #+#    #+#              #
#    Updated: 2018/01/25 22:04:50 by lgarczyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftdata.a

NAMES = \
	array/array \
	array/array_modifiers \
	array/array_wrappers \
	bitset/bitset \
	bitset/bitset_alloc \
	bitset/bitset_accessors \
	bitset/bitset_stack \
	pma/pma \
	pma/pma_modify \
	pma/pma_search \
	pma/pma_tools \
	pma/pma_wrappers \
	pma/bucket_accessors \
	pma/bucket_modify \
	pma/bucket_rebalance \
	pma/bucket_tools \
	pma/pmait \
	pma/pmait_delete \
	queue/queue \
	queue/queue_modifiers \
	sorted/sorted \
	sorted/sorted_accessors \
	sorted/sorted_delete \
	sorted/sorted_insert \
	sorted/sorted_replace \
	sorted/sorted_search


OBJ = $(addprefix obj/, $(addsuffix .o, $(NAMES)))
SRC = $(addprefix src/, $(addsuffix .c, $(NAMES)))

INC = -I../libft/includes -Iincludes

LIB = -L ../libft/ -lft

DEB = -g -g3 #-fsanitize=address

OPT = #-O3

FLG = -Wall -Wextra -Werror -funsigned-char $(DEB)

all: $(NAME)

$(NAME):$(OBJ)
	ar -rcsT  $(NAME) ../libft/libft.a $(OBJ)

obj/%.o: src/%.c includes/data.h
	mkdir -p `dirname $@`
	gcc -o $@ -c $< $(INC) $(FLG)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(TNAME)

re: fclean all

optire: fclean opti
