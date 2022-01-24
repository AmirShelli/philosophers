NAME = philo
BONUS = philo_bonus

SRCS =  $(shell find . -type f -name "*.c" ! -name "*_bonus.c")
BONUS_SRCS =  $(shell find . -type f -name "*_bonus.c")

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

HEADER = $(wildcard ./philo_mandatory/inc/*.h)
HEADER_BONUS = $(wildcard ./philo_bonus/inc/*.h)

CC = gcc -Wall -Werror -Wextra

$(NAME): $(OBJS) $(HEADER)
	$(CC) -pthread $(OBJS) -o $(NAME)

bonus: $(BONUS_OBJS) $(HEADER_BONUS)
	@$(CC) -I ./philo_bonus/inc $(BONUS_OBJS) -o $(BONUS)

%.o: %.c
	@$(CC) $(CFLAGS) -I ./philo_mandatory/inc $< -c -o $@

clean:
	@rm -rf $(wildcard ./*.o)
	@rm -rf $(wildcard ./*/*.o)
	@rm -rf $(wildcard ./*/*/*.o)

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(BONUS)

re : fclean all

.PHONY: all libft clean fclean re