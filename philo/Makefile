# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 18:43:33 by lfarias-          #+#    #+#              #
#    Updated: 2022/12/22 15:16:18 by lfarias-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	philo
CFLAGS 	= 	-Wall -Wextra -Werror -g 
#-fsanitize=thread
LDFLAGS	=	-lpthread 
#-fsanitize=thread
SRC 	= 	main.c \
			philosopher.c \
			input.c \
			matrix.c \
			matrix_reloaded.c \
			printer.c \
			philo_actions.c \
			philo_actions2.c \
			fork.c \
			clockmaker.c \
			ph_calloc.c \
			ft_atoll.c \
			utils.c
SRC_OBJ	= 	$(SRC:.c=.o)

$(NAME): $(SRC_OBJ) 
	cc $(CFLAGS) $(SRC_OBJ) $(LDFLAGS) -o $(NAME)

all: $(NAME)

clean: 
	rm -f $(SRC_OBJ)

fclean: clean
	rm -f ./philo

re: fclean all

run: all
	./$(NAME) 4 310 200 100 

r1: all
	./$(NAME) 4 410 200 200

r2: all
	./$(NAME) 4 800 200 200

.PHONY:
	all clean fclean re run r1 r2
