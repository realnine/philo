CC		= gcc -pthread -g3

SRCS	= main.c init.c utils.c msg.c routine.c checker.c deallocate.c 

NAME	= philo

all : $(NAME)

$(NAME) :
	$(CC) $(SRCS) -o $(NAME)

clean :
	rm $(NAME)

fclean :
	rm -rf $(NAME) $(NAME).dSYM

re : fclean $(NAME)

.PHONY : all clean fclean re