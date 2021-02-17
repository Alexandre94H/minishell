SOURCES				=	utils/get_next_line_utils.c \
						utils/get_next_line.c \
						utils/ft_put.c \
						utils/ft_split.c \
						utils/ft_strndup.c \
						utils/ft_stristr.c \
						utils/ft_atoi.c \
						utils/ft_equals.c \
						utils/ft_replace.c \
						utils/ft_isalnum.c \
						utils/ft_itoa.c \
						utils/ft_rmchar.c \
						utils/ft_addtab.c \
						utils/env.c \
						functions/f_echo.c \
						functions/f_cd.c \
						functions/f_pwd.c \
						functions/f_export.c \
						functions/f_unset.c \
						functions/f_env.c \
						functions/f_exit.c \
						srcs/call_function.c \
						srcs/args.c \
						srcs/execute.c \
						srcs/arrow.c \
						srcs/dispatch.c \
						srcs/prompt.c \
						srcs/sig.c \
						srcs/main.c

OBJECTS				=	${SOURCES:.c=.o}

NAME				=	minishell

COMPILE				=	cc
REMOVE				=	rm -f

COMPILATION_FLAGS	=	-Wall -Wextra -Werror

.c.o:
	${COMPILE} ${COMPILATION_FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJECTS}
	${COMPILE} -o ${NAME} ${OBJECTS}

all: ${NAME}

clean:
	${REMOVE} ${OBJECTS}

fclean: clean
	${REMOVE} ${NAME}

re: fclean all

.PHONY: all clean fclean re