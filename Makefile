# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbach <cbach@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 22:27:45 by cbach             #+#    #+#              #
#    Updated: 2020/11/15 13:18:57 by cbach            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell
FLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft

GNL_DIR = get_next_line

MINISHELL_DIR = .

PARSER_DIR = parser

EXECUTOR_DIR = executor

EXECUTOR_CMDS_DIR = $(EXECUTOR_DIR)/cmds

EXECUTOR_UTILS_DIR = $(EXECUTOR_DIR)/utils

HEADERS =											\
			$(wildcard $(LIBFT_DIR)/*.h)			\
			$(wildcard $(GNL_DIR)/*.h)				\
			$(wildcard $(MINISHELL_DIR)/*.h)		\
			$(wildcard $(PARSER_DIR)/*.h)			\
			$(wildcard $(EXECUTOR_DIR)/*.h)			\
			$(wildcard $(EXECUTOR_CMDS_DIR)/*.h)	\
			$(wildcard $(EXECUTOR_UTILS_DIR)/*.h)	

SRC = 		$(wildcard $(GNL_DIR)/*.c)				\
			$(wildcard $(MINISHELL_DIR)/*.c)		\
			$(wildcard $(PARSER_DIR)/*.c)			\
			$(wildcard $(EXECUTOR_DIR)/*.c)			\
			$(wildcard $(EXECUTOR_CMDS_DIR)/*.c)	\
			$(wildcard $(EXECUTOR_UTILS_DIR)/*.c)


OBJ = 		$(patsubst %.c, %.o, $(SRC))
OBJ_BONUS = $(patsubst %.c, %.o, $(BONUS))

ifdef BONUS_FILES
OBJ_FILES = $(OBJ_BONUS)
else
OBJ_FILES = $(OBJ)
endif

.PHONY: all bonus clean fclean re make_libft


all: make_libft $(NAME)
	@rm -f .depend

make_libft:
	$(MAKE) -C $(LIBFT_DIR) bonus
	$(MAKE) -C $(LIBFT_DIR) all

$(NAME): $(OBJ_FILES)
	gcc $(FLAGS) $(OBJ_FILES) -L${LIBFT_DIR} -lft -o $(NAME)

bonus:
	$(MAKE) BONUS_FILES=1 all

.depend: $(SRC) $(BONUS)
	@rm -f .depend
	gcc $(FLAGS) -MM $^ > .depend

-include .depend

%.c:
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS) 
	@rm -f .depend
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all -s --track-fds=yes ./minishell