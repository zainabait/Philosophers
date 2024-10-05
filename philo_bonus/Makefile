# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/02 16:17:44 by zait-bel          #+#    #+#              #
#    Updated: 2024/08/17 14:17:31 by zait-bel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = philo_bonus.c philo_helper_bonus.c philo_helper2_bonus.c

OBJS = $(SRC:.c=.o)


NAME = philo_bonus

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


%.o: %.c philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: clean 
