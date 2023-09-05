NAME = philo

SRC_C = main.c inits.c actions.c parsing.c utils.c
SRC_DIR = Source/
SRC = $(addprefix $(SRC_DIR), $(SRC_C))

FLAGS = -Wall -Wextra -Werror -lpthread
INCLUDE = #-fsanitize=thread -g 

OBJ_DIR = ./objects/
OBJ = $(addprefix $(OBJ_DIR), $(SRC_C:.c=.o))

GREEN='\033[1;32m'
LIGHT_BLUE='\033[1;36m'
NONE='\033[0m'
BLUE='\033[1;34m'

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(OBJ) $(LIBFT) $(INCLUDE) -o $(NAME)
	echo $(GREEN)"- Compiled -"$(NONE)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	gcc $(FLAGS) -c $< -o $@

clean:
	echo $(BLUE)"- Cleaning philo -"$(NONE)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT: $(NAME) $(OBJ) all clean fclean re