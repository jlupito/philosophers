NAME = philo
CC = gcc 
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread -g 
INCLUDES = -I./include

#source
SRCS_DIR = sources/
SRCS = main.c init.c utils.c actions.c \

SRCS_PREFIXED = $(addprefix $(SRCS_DIR), $(SRCS))

#objsm
OBJS = $(SRCS_PREFIXED:.c=.o)

all : $(NAME)

%.o: %.c ./include/philo.h
	$(CC) $(CFLAGS) -c $< -o $@
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo $(NAME) is built

clean :
	@rm -rf $(OBJS)
	@echo cleaning

fclean : clean
	@rm -rf $(NAME)
	@echo "full clean"

re : fclean all

.PHONY	: all clean fclean re help