# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 17:24:20 by ojebbari          #+#    #+#              #
#    Updated: 2023/12/09 02:31:47 by ojebbari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c minishell.c ./utils/spliting.c ./utils/utils.c ./utils/expand.c \
		./tokenize/tokenize.c ./tokenize/tokenize_utils.c ./parser/parser.c  \
		./parser/parser_utils.c ./parser/parser_list.c 						 \
		./tokenize/tokenize_list.c ./utils/quotes.c ./utils/syntax_error.c   \
		./execution/ft_echo.c ./execution/ft_pwd.c ./execution/ft_exit.c     \
		./execution/ft_env.c ./execution/ft_export.c ./execution/ft_cd.c     \
		./execution/ft_unset.c ./execution/fill_list.c ./execution/exe.c     \
		./utils/utils1.c ./execution/ft_signals.c ./utils/ft_lstnew.c        \
		./utils/ft_lstadd_back.c  ./libc/libc.c ./utils/expand_here_doc.c    \
		./libc/libc1.c ./libc/libc2.c ./libc/libc3.c ./libc/libc4.c          \
		./execution/exe1.c ./execution/exe2.c ./execution/exe3.c             \
		./execution/exe4.c ./execution/exe5.c ./execution/export1.c          \


CFLAGS = -Wall -Wextra -Werror
CC = cc
NAME = minishell
RM = rm -fr
OBJ = $(SRC:.c=.o)

#Colors:

GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m
BLUE		=   \e[34m
BLACK		=   \e[30m
RED			=	\e[31m
CYANA		=	\e[36m
WHITE		=	\e[37m

all : $(NAME)

%.o : %.c minishell.h
	@printf "$(CURSIVE)$(GRAY) 	- Making object file $(notdir $@) from source file $(notdir $<) ... $(RESET)\n"
	@$(CC) $(CFLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@

$(NAME) : $(OBJ)
	@printf "$(CURSIVE)$(CYANA)  	- Compiling :$(RESET)\n"
	@printf "$(WHITE)                        ________________________________________   \n"
	@printf "$(WHITE)                    \"                                             \"\n"
	@printf "$(GREEN)                    \"   █▀▄▀█ ░▀░ █▀▀▄ ░▀░ █▀▀ █░░█ █▀▀ █░░ █░░   \"\n"
	@printf "$(YELLOW)                    \"   █░▀░█ ▀█▀ █░░█ ▀█▀ ▀▀█ █▀▀█ █▀▀ █░░ █░░   \"\n"
	@printf "$(RED)                    \"   ▀░░░▀ ▀▀▀ ▀░░▀ ▀▀▀ ▀▀▀ ▀░░▀ ▀▀▀ ▀▀▀ ▀▀▀   \"\n"
	@printf "$(WHITE)                    \"   ________________________________________  \"\n\n"
	@$(CC) -L$(shell brew --prefix readline)/lib -lreadline  $(CFLAGS) $(OBJ) -o $@

clean :
	@printf "$(YELLOW)	- Removing object files ... \n"
	@printf "$(CURSIVE)$(GRAY)	  - Object files removed.$(RESET)\n"	
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)
	@printf "$(GREEN)	- Removing $(NAME)... $(RESET)\n"
	@printf "$(CURSIVE)$(GRAY)	  - Executable removed.$(RESET)\n\n"

re : fclean all

push:
	@make fclean
	@git add *
	@git commit -am "$(msg)"
	@git push

merge-lberkani-in:
	@make fclean
	@git checkout main
	@git pull origin main
	@git merge l-berkani
	@git push origin main
	@git checkout l-berkani

merge-oussama-in:
	@make fclean
	@git checkout main
	@git pull origin main
	@git merge oussama
	@git push origin main
	@git checkout oussama

merge-lberkani-out: 
	@make fclean
	@git checkout l-berkani
	@git pull origin l-berkani
	@git merge main
	@git push origin l-berkani

merge-oussama-out:
	@make fclean
	@git checkout oussama
	@git pull origin oussama
	@git merge main
	@git push origin oussama
