NAME	=	container

SRCS	=	main.cpp

GCC		=	clang++

FLAGS	=	-Werror -Wextra -Wall -std=c++98

OBJS	=	${SRCS:.cpp=.o}

HDRS	=	vector.hpp iterator.hpp

all		:	${NAME}

${NAME}	:	${OBJS}
			${GCC} ${FLAGS} -o ${NAME} ${OBJS}

%.o		:	%.cpp
			${GCC} ${FLAGS} -o $@ -c $<

${OBJS}	:	${HDRS}

clean	:
			rm -rf ${OBJS}

fclean	:	clean
			rm -rf ${NAME}

re	:		fclean all

.PHONY:	all clean fclean re
