# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 13:02:03 by mbaumgar          #+#    #+#              #
#    Updated: 2024/07/18 11:19:53 by mbaumgar         ###   ########.fr        #
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
MAUVE		= \033[0;34m
RED			= \033[0;31m
END			= \033[m

# ╔═╗╔═╗╦ ╦╦═╗╔═╗╔═╗╔═╗
# ╚═╗║ ║║ ║╠╦╝║  ║╣ ╚═╗
# ╚═╝╚═╝╚═╝╩╚═╚═╝╚═╝╚═╝

SRC_DIR		= ./src/
OUT_DIR		= ./bin/

SRC			= minishell.c \
			parsing/parser.c \
			parsing/lexer.c \
			parsing/expander.c \
			builtin/cd.c \
			builtin/echo.c \
			builtin/env.c \
			builtin/exit.c \
			builtin/export.c \
			builtin/pwd.c \
			builtin/unset.c \
			exec/exec_cmd.c \
			exec/vractest.c \
			utils/execution.c \
			utils/token_lst.c \
			utils/envp.c

OBJ			= ${SRC:%.c=${OUT_DIR}%.o}

# ╦═╗╦ ╦╦  ╔═╗╔═╗
# ╠╦╝║ ║║  ║╣ ╚═╗
# ╩╚═╚═╝╩═╝╚═╝╚═╝

all: ${NAME}

${LFT}: 
	@${MAKE_LIBFT}

${NAME}: ${LFT} ${OBJ}
	${CC} ${CFLAGS} -o ${NAME} ${OBJ} ${LFT} ${LIBS}
	@echo "${MAUVE}\n. - . - . - . - . - . - . - .${END}\n"
	@echo "${DUCK}        S h e l l - C\n          s M i L e${END}\n"
	@echo "${MAUVE}        f x X K i N g\n          r E a d Y${END}\n"
	@echo "${DUCK}- . - . - . - . - . - . - . -${END}\n"
	@echo "${FLUO}Enjoy.${END}"

${OUT_DIR}%.o: %.c
	@mkdir -p ${@D}
	${CC} ${CFLAGS} -g3 -c $< -o $@ 

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
	norminette utils/*
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
