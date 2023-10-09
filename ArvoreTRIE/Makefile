NAME = trie
SRCS = main.c trie.c
OBJS = $(SRCS:.c=.o)


all: $(NAME)


$(NAME): $(OBJS)
	gcc $(OBJS) -o $(NAME)

$(OBJS):
	gcc -c $(SRCS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re