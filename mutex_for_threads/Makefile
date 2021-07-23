
NAME	= philo_in_threads
HEADER	= philo_in_threads.h
SRCS	= clean.c controler.c ft_atoi.c philo.c start_routine.c \
		threads.c time.c utils.c
# $(shell find . -type f -name '*.c')
OBJS	= $(SRCS:.c=.o)
TEXT	= "      ./philo_in_threads compiled"
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
LIBS	= -lpthread

.PHONY: clean fclean all bonus

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) ${OBJS} ${LIBS} -o ${NAME}
	@echo "======================="
	@echo $(TEXT)
	@echo "======================="

%.o:%.c $(HEADER) 
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(shell find . -type f -name '*.o')

fclean: clean
	rm -f $(NAME)

re: fclean all
