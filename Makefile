# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebakirog <ebakirog@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 22:41:15 by ebakirog          #+#    #+#              #
#    Updated: 2024/02/07 23:15:27 by ebakirog         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	philo
CC 		:=	gcc
FLAGS 	:=	-Wall -Wextra -Werror
SRC 	:=	philo.c\
			life_loop.c\
			utils.c
OBJ		:= 	$(SRC:.c=.o)

RED 	:= 	\033[1;31m
GREEN 	:= 	\033[1;32m
YELLOW  := 	\033[1;33m
RESET	:= 	\033[1m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Philo compiled successfully ✅$(RESET)"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@echo "$(YELLOW)Objects files successfully deleted 📁$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)Philo and Objects files successfully deleted ❌$(RESET)"

re: fclean all

.PHONY: all clean fclean re