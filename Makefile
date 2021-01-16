NAME	=	container

SRCS	=	main.cpp

GCC		=	clang++

FLAGS	=	-Werror -Wextra -Wall -std=c++98 -g3 -fsanitize=address

OBJS	=	${SRCS:.cpp=.o}

HDRS	=	containers/*.hpp utils/*.hpp test_list.hpp

all		:	${NAME}

${NAME}	:	${OBJS}
			${GCC} ${FLAGS} -o ${NAME} ${OBJS}

%.o		:	%.cpp
			${GCC} ${FLAGS} -o $@ -c $<

${OBJS}	:	${HDRS}

test	:
			${GCC} ${FLAGS} -o main_it.o -c main_it.cpp
			${GCC} ${FLAGS} -o test main_it.o

clean	:
			rm -rf *.o

fclean	:	clean
			rm -rf ${NAME}

re	:		fclean all

.PHONY:	all clean fclean re
