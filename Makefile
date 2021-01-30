SOURCES				=	get_next_line/get_next_line_utils.c \
						get_next_line/get_next_line.c \
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