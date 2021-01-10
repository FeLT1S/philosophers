# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/15 18:58:18 by jiandre           #+#    #+#              #
#    Updated: 2021/01/10 20:52:53 by jiandre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo_three

OBJ_FILES = philo_three.o philo_utils.o philo_life.o philo_print.o philo_fork.o

CFLAGS = -Wall -Wextra -O0

all: $(NAME)

$(NAME): $(OBJ_FILES) philo_three.h
	clang $(OBJ_FILES) -o $(NAME)

%.o: %.c
	clang -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all