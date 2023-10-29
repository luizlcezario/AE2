NAME = hash
SRCS = main.c hash.c
OBJS = $(SRCS:.c=.o)


all: $(NAME)


$(NAME): $(OBJS)
	gcc $(OBJS) -o $(NAME) -fsanitize=address  -g3

$(OBJS):
	gcc -c $(SRCS) -fsanitize=address -g3

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re