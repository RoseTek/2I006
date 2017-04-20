SRCS	=	Src/MainGraphe.c		\
		Src/Graphe.c			\
		Src/entree_sortie.c		\
		Src/SVGwriter.c			\
		Src/Struct_File.c		\
		Src/Struct_Liste.c		\
		Src/evaluation_NChaines.c	\
		Src/shortPath.c			\
		Src/shortPathDjikstra.c		\
		Src/Tas.c

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
