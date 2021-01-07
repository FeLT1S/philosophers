# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/15 18:58:18 by jiandre           #+#    #+#              #
#    Updated: 2021/01/08 20:55:41 by jiandre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo_two

OBJ_FILES = philo_two.o philo_utils.o philo_life.o philo_print.o philo_fork.o

CFLAGS = -Wall -Wextra -O0

all: $(NAME)

$(NAME): $(OBJ_FILES) philo_two.h
	clang $(OBJ_FILES) -o $(NAME)

%.o: %.c
	clang -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all