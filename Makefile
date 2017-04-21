SRCS	=	$(shell find Src -name '*.c')

OBJS	=	$(SRCS:.c=.o)

NAME	=	MainGraphe

RM	=	rm -f

CFLAGS	=	-lm -I./Inc -O3

CC	=	gcc

.SILENT: 

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean: 
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
