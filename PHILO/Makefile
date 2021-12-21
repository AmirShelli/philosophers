NAME = philo
BONUS = bonus

SRCS =  $(shell find src -type f -name "*.c")
BONUS_SRCS =  

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

INCLUDES = -I ./inc 

CC = gcc -Wall -Werror -Wextra

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

bonus: $(BONUS_OBJS)
	@$(CC) $(INCLUDES) $(BONUS_OBJS) -o $(BONUS)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) $< -c -o $@

clean :
	@rm -rf $(wildcard ./*.o)
	@rm -rf $(wildcard ./*/*.o)
	@rm -rf $(wildcard ./*/*/*.o)

fclean : clean
	@$(MAKE) fclean -sC ./libft
	@rm -rf $(NAME)
	@rm -rf $(BONUS)

re : fclean all

.PHONY: all libft clean fclean re