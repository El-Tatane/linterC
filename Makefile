CC	 = gcc

RM	 = rm -rf

NAME	 = Linter


CFLAGS	 +=  -IInclude
LDFLAGS  = -Werror -W -Wall

SRC	 =  Src/main.c \
		Src/keysFunction.c
		

OBJ	 = $(SRC:.c=.o)

all:	  $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) 

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
