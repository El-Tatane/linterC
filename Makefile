CC	 = gcc

RM	 = rm -rf

NAME	 = Linter


CFLAGS	 +=  -IInclude  -g3
LDFLAGS  = -Werror -W -Wall 

SRC	 =  Src/main.c \
		Src/Part1/keysFunction.c \
		Src/Part1/extendLinkedList.c \
		Src/Part2/mainLinter.c \
		Src/Part2/singleLineRules.c \
		Src/Part2/multiLinesRules.c \
		Src/createScopeList.c \
		Src/scopeList.c \
		Src/tvarList.c
		

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
