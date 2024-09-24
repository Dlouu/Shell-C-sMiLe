# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 13:02:03 by mbaumgar          #+#    #+#              #
#    Updated: 2024/09/24 16:11:42 by mbaumgar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

# ╔═╗╦  ╔═╗╔═╗╔═╗
# ╠╣ ║  ╠═╣║ ╦╚═╗
# ╚  ╩═╝╩ ╩╚═╝╚═╝

CC			= cc
ARFLAGS 	= -crs
RM			= rm -rf
CFLAGS		= -Wall -Werror -Wextra
DBG_LEAK	= -fsanitize=address -fsanitize=leak -g3
DBG_ADDRESS	= -fsanitize=address -g3
DBG_THREAD	= -fsanitize=thread -g3

LFT			= ./libft/libft.a
LIBS		= -lreadline
LIBFT		= ./libft
MAKE_LIBFT	= ${MAKE} --no-print-directory -C ${LIBFT}

# ╔═╗╔═╗╦  ╔═╗╦═╗╔═╗
# ║  ║ ║║  ║ ║╠╦╝╚═╗
# ╚═╝╚═╝╩═╝╚═╝╩╚═╚═╝
 
DUCK		= \033[38;2;8;195;187m
FLUO		= \033[38;2;223;255;0m
BLU			= \033[0;34m
RED			= \033[0;31m
END			= \033[m

# ╔═╗╔═╗╦ ╦╦═╗╔═╗╔═╗╔═╗
# ╚═╗║ ║║ ║╠╦╝║  ║╣ ╚═╗
# ╚═╝╚═╝╚═╝╩╚═╚═╝╚═╝╚═╝

SRC_DIR		= ./src/
OUT_DIR		= ./bin/

SRC			= minishell.c \
			signals.c \
			parsing/lexer.c \
			parsing/tokenizer.c \
			parsing/expander.c \
			parsing/recombiner.c \
			parsing/parser.c \
			parsing/splitter.c \
			parsing/sorter.c \
			parsing/envp.c \
			parsing/error.c \
			parsing/var.c \
			parsing/quotes.c \
			parsing/token_lst.c \
			parsing/token_print.c \
			builtin/cd.c \
			builtin/echo.c \
			builtin/env.c \
			builtin/exit.c \
			builtin/export.c \
			builtin/export_utils.c \
			builtin/pwd.c \
			builtin/unset.c \
			exec/exec.c \
			exec/exec_cmd_utils.c \
			exec/heredoc.c \
			exec/redir.c \
			exec/tab_converter.c \
			exec/utils.c \
			utils/pipe_utils.c

OBJ			= ${SRC:%.c=${OUT_DIR}%.o}

# ╦═╗╦ ╦╦  ╔═╗╔═╗
# ╠╦╝║ ║║  ║╣ ╚═╗
# ╩╚═╚═╝╩═╝╚═╝╚═╝

all: ${NAME}

${LFT}: 
	@${MAKE_LIBFT}

${NAME}: ${LFT} ${OBJ}
	@${CC} ${CFLAGS} -o ${NAME} ${OBJ} ${LFT} ${LIBS}
	@echo "${BLU}[${END} ${DUCK}Shell-[C]_sMiLe${END} ready! 🐚 • 👀 • 😃 ${BLU}]"
	@echo "[${END} Launch it with ${FLUO}./minishell${END} command. ${BLU}]"
	@echo "${END}"

${OUT_DIR}%.o: %.c
	@mkdir -p ${@D}
	@${CC} ${CFLAGS} -g3 -c $< -o $@ 

clean:
	@${MAKE_LIBFT} clean
	${RM} ${OUT_DIR}
	@echo "🧹 ${RED}removed:${END} objects"

fclean: clean
	${RM} ${NAME}
	@${MAKE_LIBFT} fclean
	@echo "🧹 ${RED}removed:${END} minishell\n"

re: fclean all

uwu: re
	@${MAKE} --no-print-directory clean

norminette:
	@echo "\n"
	norminette libft/inc/*
	@echo "\n"
	norminette inc/d* inc/m* inc/p* inc/t*
	@echo "\n"
	norminette libft/src/*
	@echo "\n"
	norminette parsing/*
	@echo "\n"
	norminette utils/en* utils/tok*
	@echo "\n"
	norminette minishell.c

leak: re
	${CC} ${CFLAGS} ${DBG_LEAK} -o ${NAME} ${OBJ} ${LFT}

address: re
	${CC} ${CFLAGS} ${DBG_ADDRESS} -o ${NAME} ${OBJ} ${LFT}

thread: re
	${CC} ${CFLAGS} ${DBG_THREAD} -o ${NAME} ${OBJ} ${LFT}

main: fclean
	cd ..
	git add .
	git commit -m "${m}"
	git push origin main

nils: fclean
	cd ..
	git add .
	git commit -m "Nils : ${m}"
	git push origin nils

dlou: fclean
	cd ..
	git add .
	git commit -m "Dlou : ${m}"
	git push origin dlou

.PHONY: all clean fclean re uwu norminette leak address thread main nils dlou
