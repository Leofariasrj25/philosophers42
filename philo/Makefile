# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 18:43:33 by lfarias-          #+#    #+#              #
#    Updated: 2022/12/05 15:55:16 by lfarias-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	philo
CFLAGS 	= 	-Wall -Wextra -Werror -g
LDFLAGS	=	-lpthread
SRC 	= 	main.c \
			philosopher.c \
			input.c \
			matrix.c \
			printer.c \
			ft_atoll.c
SRC_OBJ	= 	$(SRC:.c=.o)

$(NAME): $(SRC_OBJ) 
	cc $(CFLAGS) -fsanitize=address $(SRC_OBJ) $(LDFLAGS) -o $(NAME)

all: $(NAME)

clean: 
	rm -f $(SRC_OBJ)

fclean: clean
	@rm -f ./philo

re: clean all

run: all
	./$(NAME) 5 1000 1000 1000


