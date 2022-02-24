# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marmand <marmand@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/05 17:25:52 by marmand           #+#    #+#              #
#    Updated: 2022/01/08 20:48:41 by marmand          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
NAME_BONUS = philo_bonus

SRCS = ft_fork.c ft_philo.c ft_utils.c philo.c
SRCS_BONUS = ft_clear_bonus.c ft_init_bonus.c ft_philo_simul_bonus.c \
				ft_utils_bonus.c philo_bonus.c

HEADER = philo.h
HEADER_BONUS = philo_bonus.h

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

FLAGS = -Wextra -Werror -Wall -pthread

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $(NAME) 

$(NAME_BONUS): $(OBJS_BONUS)
	gcc $(FLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

%.o : %.c
	gcc $(FLAGS) -c $<

$(OBJS): $(HEADER)

$(OBJS_BONUS): $(HEADER_BONUS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all

bonus: $(NAME_BONUS)
