# ********************************************* #
#                                               #
#    Makefile                                   #
#                                               #
#    By: Eduardo                                #
#                                               #
#    Created: 2022/06/04 17:28:42 by Eduardo    #
#    Updated: 2022/06/04 17:28:43 by Eduardo    #
#                                               #
# ********************************************* #


NAME =  hashtable.a
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
HEADERS = $(wildcard *.h)
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${HEADERS} ${OBJS}
	ar rcs ${NAME} ${OBJS}

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${OBJS} ${NAME}

re: fclean all

git:
	git add .
	git commit -m "$m"
	git push

.PHONY: all clean fclean re