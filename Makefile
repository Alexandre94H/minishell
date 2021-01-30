SOURCES				=	utils/get_next_line_utils.c \
						utils/get_next_line.c \
						utils/ft_put.c \
						utils/ft_split.c \
						utils/ft_strndup.c \
						utils/ft_atoi.c \
						utils/ft_equals.c \
						utils/env.c \
						functions/f_echo.c \
						functions/f_exit.c \
						call_function.c \
						execute.c \
						dispatch.c \
						prompt.c \
						main.c

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