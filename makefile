NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -Iinclude
SRC = src

SRCS = $(SRC)/main.c \
       $(SRC)/init.c \
       $(SRC)/utils.c \
       $(SRC)/routine.c \
       $(SRC)/monitor.c \
       $(SRC)/simulation.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re