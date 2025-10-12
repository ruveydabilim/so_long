NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_printf.c ft_putchar.c ft_putnbr.c ft_putstr.c ft_putunbr_fd.c\
		ft_puthex_fd.c ft_putmem_fd.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re