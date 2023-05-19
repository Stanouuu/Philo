# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbarrage <sbarrage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 12:19:48 by sbarrage          #+#    #+#              #
#    Updated: 2023/03/17 15:51:03 by sbarrage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c free.c checker.c initialize.c utils.c philo.c

INCLUDES = -I ./include/

PRINTF = ./source/Printf/libftprintf.a

PRINTFINC = -I ./source/Printf

SRC_DIR = source

OBJ_DIR = objet

SRCS = $(SRC:%=$(SRC_DIR)/%)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

GCC = gcc

FLAGS = -Wall -Wextra -Werror -g3 -pthread

RM = rm -rf

MKDIR = mkdir -p

all:	$(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(OBJ_DIR)
	$(GCC) $(FLAGS) $(LIBFTINC) $(PRINTFINC) $(INCLUDES) -c $< -o $@
	
$(NAME):	$(OBJS)
	@echo "Compiling Philosopher"
	make -C ./source/Printf
	$(GCC) $(FLAGS) -o $(NAME) $(LIBFTINC) $(PRINTFINC) $(INCLUDES) $(OBJS) $(LIBFT) $(PRINTF)
	@echo "Compilation completed "

clean:
	$(RM) $(OBJ_DIR)
	@echo "Clean done"

fclean:	clean
	@make fclean -C ./source/Printf
	$(RM) $(NAME) $(NAMEBONUS)
	@echo "Fclean done"

re: fclean all

m: all clean

.PHONY: all clean fclean re m bonus