NAME = philo
NAME_BONUS = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread
INCLUDES = -I$(HEADERS_DIR)

HEADERS_LIST =	philo.h philo_bonus.h
HEADERS_DIR = ./includes/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRC_BONUS_DIR = ./sources_bonus/
SRC_BONUS_LIST =	main_bonus.c \
					isint_bonus.c \
					parse_bonus.c \
					child_bonus.c \
					semaphores_bonus.c \
					actions_bonus.c

SRC_DIR = ./sources/
SRC_LIST =	main.c \
			isint.c \
			parse.c \
			free.c \
			mutex.c \
			actions.c \
			pthread_util.c \
			pthread.c

SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))
SRC_BONUS = $(addprefix $(SRC_BONUS_DIR), $(SRC_BONUS_LIST))

OBJ_DIR_BONUS = ./objects_bonus/
OBJ_LIST_BONUS = $(patsubst %.c, %.o, $(SRC_BONUS_LIST))
OBJ_BONUS = $(addprefix $(OBJ_DIR_BONUS), $(OBJ_LIST_BONUS))

OBJ_DIR = ./objects/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

.PHONY : all bonus clean fclean re

all : $(NAME) bonus

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

bonus : $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_DIR_BONUS) $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_BONUS) -o $(NAME_BONUS)

$(OBJ_DIR_BONUS):
	mkdir -p $(OBJ_DIR_BONUS)

$(OBJ_DIR_BONUS)%.o: $(SRC_BONUS_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

clean :
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR_BONUS)

fclean : clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re : fclean all