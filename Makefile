CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -I.
LIBS	= -lpthread

SRCS	= main.c init.c utils.c msg.c routine.c checker.c deallocate.c 

NAME	= philo

all : $(NAME)

$(NAME) :
	$(CC) ${CFLAGS} $(SRCS) -o $(NAME) ${LIBS}

clean :
	rm $(NAME)

fclean :
	rm -rf $(NAME) $(NAME).dSYM

re : fclean $(NAME)

.PHONY : all clean fclean re