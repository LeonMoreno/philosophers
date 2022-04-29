#Variable
NAME	=	philo
SRC_DIR	=	src/
CC		=	gcc
CFLAGS	=	-Werror -Wall -Wextra -I include/
RM		= 	rm -f

#Sources Files
SRC_FILES	=	philo.c utils.c start_algo.c
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			= 	$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

.c.o :	
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean :	
			$(RM) $(OBJ)


fclean : 	clean
			$(RM) $(NAME)


re :		fclean all


.PHONY:		all clean fclean re



