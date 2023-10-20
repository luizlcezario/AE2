NAME = uf
SRCS = uf.cpp
OBJS = $(SRCS:.cpp=.o)


all: $(NAME)


$(NAME): $(OBJS)
	g++ $(OBJS) -o $(NAME) -fsanitize=address  -g3 -fpermissive

$(OBJS):
	g++ -c $(SRCS) -fsanitize=address -g3 -fpermissive

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re