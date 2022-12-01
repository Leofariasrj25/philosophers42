# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 18:43:33 by lfarias-          #+#    #+#              #
#    Updated: 2022/12/01 19:13:44 by lfarias-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = main.c philo_utils.c ft_atoll.c
SRC_OBJ = $(SRC:.c=.o)

$(NAME): $(SRC_OBJ) 
	cc -g -Wall -Wextra -Werror -fsanitize=address $(SRC_OBJ) -o $(NAME)

all: $(NAME)

clean: 
	rm -f $(SRC_OBJ)

fclean: clean
	@rm -f ./philo

re: all clean

run: all
	./$(NAME)


