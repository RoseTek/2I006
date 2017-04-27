SRCS	=	Src/main.c \
		Src/chaine.c \
		Src/entree_sortie.c\
		Src/SVGwriter.c\
		Src/reseau_liste.c \
		Src/reseau_hash.c \
		Src/reseau_quadtree.c \
		Src/reseau.c

OBJS	=	$(DIR)$(SRCS:.c=.o)
NAME	=	main
CFLAGS	=	-I./Inc

all: $(NAME)
re: fclean all
$(NAME): $(OBJS)
	gcc $(CFLAGS) -Wall -O -o $(NAME) $(OBJS) -lm
clean: 
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
