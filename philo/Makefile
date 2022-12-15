# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 18:43:33 by lfarias-          #+#    #+#              #
#    Updated: 2022/12/15 18:02:05 by lfarias-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	philo
CFLAGS 	= 	-Wall -Wextra -Werror -g 
#-fsanitize=address
LDFLAGS	=	-lpthread 
#-fsanitize=address
SRC 	= 	main.c \
			philosopher.c \
			input.c \
			matrix.c \
			printer.c \
			monitor.c \
			philo_actions.c \
			clockmaker.c \
			ph_calloc.c \
			ft_atoll.c
SRC_OBJ	= 	$(SRC:.c=.o)

$(NAME): $(SRC_OBJ) 
	cc $(CFLAGS) $(SRC_OBJ) $(LDFLAGS) -o $(NAME)

all: $(NAME)

clean: 
	rm -f $(SRC_OBJ)

fclean: clean
	@rm -f ./philo

re: fclean all

run: all
	./$(NAME) 5 1000 1000 1000


