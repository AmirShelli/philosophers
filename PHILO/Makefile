NAME = philo
BONUS = philo_bonus

SRCS =  $(shell find ./philo_m -type f -name "*.c")
BONUS_SRCS =  $(shell find ./philo_b -type f -name "*.c")

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

HEADER = $(wildcard ./philo_m/inc/*.h)
HEADER_BONUS = $(wildcard ./philo_b/inc/*.h)

CC = gcc -Wall -Werror -Wextra

$(NAME): $(OBJS) $(HEADER)
	@$(CC) -pthread -I ./philo_m/inc $(OBJS) -o $(NAME)

bonus: $(BONUS_OBJS) $(HEADER_BONUS)
	@$(CC) -pthread  -I ./philo_b/inc $(BONUS_OBJS) -o $(BONUS)

%.o: %.c
	@$(CC) $(CFLAGS) $< -c -o $@

clean:
	@rm -rf $(shell find . -type f -name "*.o")

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(BONUS)

re : fclean all

.PHONY: all libft clean fclean re