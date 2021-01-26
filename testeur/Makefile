NAME	=	test

SRCS	=	main.cpp

GCC		=	clang++

FLAGS	=	-Werror -Wextra -Wall -std=c++98 -g3 -fsanitize=address

OBJS	=	${SRCS:.cpp=.o}

HDRS	=	../containers/vector.hpp test_vector.hpp

all		:	${NAME}

${NAME}	:	${OBJS}
			${GCC} ${FLAGS} -o ${NAME} ${OBJS}

%.o		:	%.cpp
			${GCC} ${FLAGS} -o $@ -c $<

${OBJS}	:	${HDRS}

diff	:	all
			./${NAME}
			diff output/ft_vector.txt output/std_vector.txt
clean	:
			rm -rf *.o

fclean	:	clean
			rm -rf ${NAME}

re	:		fclean all

.PHONY:	all clean fclean re
