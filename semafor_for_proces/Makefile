NAME	= philo_in_proc
HEADER	= philo_in_proc.h
SRCS	= $(shell find . -type f -name '*.c')
OBJS	= $(SRCS:.c=.o)
TEXT	= "      ./philo_in_proc compiled"
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -pthread
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
