CC		= gcc -pthread

SRCS	= main.c init.c utils.c message.c routine.c check_stop.c

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