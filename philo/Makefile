# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 11:09:48 by zait-bel          #+#    #+#              #
#    Updated: 2024/08/17 15:12:39 by zait-bel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = philo.c philo_helper.c philo_time.c



OBJS = $(SRC:.c=.o)


NAME = philo

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: clean 
