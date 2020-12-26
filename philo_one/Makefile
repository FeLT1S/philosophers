# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/15 18:58:18 by jiandre           #+#    #+#              #
#    Updated: 2020/12/26 16:07:50 by jiandre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo_one

OBJ_FILES = philo_one.o philo_utils.o philo_life.o

CFLAGS = -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJ_FILES) philo_one.h
	clang $(OBJ_FILES) -o $(NAME)

%.o: %.c
	clang -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all