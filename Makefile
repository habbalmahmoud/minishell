NAME = minishell

HEADER = ./includes/minishell.h

AUTHOR = nkanaan && mhabbal

LIBFT = lib/libft.a

CC = gcc

CFLAGS = -Werror -Wall -Wextra -I $(HEADER) #-fsanitize=address

SRCS = main lexer/lexer init/init builtins/pwd builtins/cd builtins/env builtins/handle_builtins utils/prompt_utils

SRC = $(addprefix src/, $(addsuffix .c, $(SRCS)))

SHELL := /bin/bash

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m
OK_COLOR    	= \033[0;32m
_END		=	\e[0m
_GREEN		=	\e[32m
_WHITE		=	\e[37m
_MUP		=	\e[1A
_ERASE		=	\e[K

OBJS = $(addprefix objs/, $(addsuffix .o, $(SRCS)))

all: header $(NAME)

	@printf "\033[?25h"
header:
	@printf "%b" "$(OK_COLOR)"
	@echo ".------..------."
	@echo "|4.--. ||2.--. |"
	@echo "| :/\: || (\/) |"
	@echo "| :\/: || :\/: |"
	@echo "| '--'4|| '--'2|"
	@echo "'------''------'"
	@echo "THE DREAM TEAM"

	@printf "%b" "$(OBJ_COLOR)Author:	$(WARN_COLOR)$(AUTHOR)$(NO_COLOR)\n"
	@echo

objs/%.o:	src/%.c
			@mkdir -p $(dir $@)
			@${CC} ${FLAGS} -c $< -o $@

$(NAME):	$(OBJS) $(LIBFT) $(HEADER)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline
			@printf "%-53b%b" "$(COM_COLOR)Project Compiled:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

$(LIBFT):
			@make -C ./lib
			@printf "%-53b%b" "$(COM_COLOR)LIBFT Compiled:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"


clean:
			rm -rf $(OBJS) ./objs
			@make clean -C ./lib
			@printf "%-53b%b" "$(COM_COLOR)OBJECT FILES DELETED:" "$(ERROR_COLOR)[✓]$(NO_COLOR)\n"


fclean:		clean
				rm $(NAME)
				rm ./lib/libft.a
				@printf "%-53b%b" "$(COM_COLOR)ALL CLEAN:" "$(ERROR_COLOR)[✓]$(NO_COLOR)\n"

re:			fclean all

.PHONY: 	all clean fclean re

.SILENT: 	clean fclean re all
