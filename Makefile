NAME	=	container

SRCS	=	main.cpp

GCC		=	clang++

FLAGS	=	-Werror -Wextra -Wall -std=c++98 -g -fsanitize=address

OBJS	=	${SRCS:.cpp=.o}

HDRS	=	containers/*.hpp utils/*.hpp utils/ABR/*.hpp utils/iterator/*.hpp

all		:	${NAME}

${NAME}	:	${OBJS}
			@${GCC} ${FLAGS} -o ${NAME} ${OBJS}

%.o		:	%.cpp
			@${GCC} ${FLAGS} -o $@ -c $<

${OBJS}	:	${HDRS}

test	:
			${GCC} ${FLAGS} -o iterator.o -c iterator.cpp
			${GCC} ${FLAGS} -o test iterator.o

clean	:
			rm -rf *.o

fclean	:	clean
			rm -rf ${NAME}

re	:		fclean all

.PHONY:	all clean fclean re
