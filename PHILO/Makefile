NAME = philo
BONUS = philo_bonus

SRCS =  $(shell find src -type f -name "*.c" ! -name "*_bonus.c")
BONUS_SRCS =  $(shell find src -type f -name "*.c" ! -name "philo.c")

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

HEADER = $(wildcard ./inc/*.h)

CC = gcc -Wall -Werror -Wextra

$(NAME): $(OBJS) $(HEADER)
	$(CC) -pthread $(OBJS) -o $(NAME)

bonus: $(BONUS_OBJS) $(HEADER)
	@$(CC) -I ./inc $(BONUS_OBJS) -o $(BONUS)

%.o: %.c
	@$(CC) $(CFLAGS) -I ./inc $< -c -o $@

clean:
	@rm -rf $(wildcard ./*.o)
	@rm -rf $(wildcard ./*/*.o)
	@rm -rf $(wildcard ./*/*/*.o)

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(BONUS)

re : fclean all

.PHONY: all libft clean fclean re