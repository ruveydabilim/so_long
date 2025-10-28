NAME = so_long

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
SRC = main.c map_parser.c map_validation.c so_long.c
GNL = ./external/get_next_line/get_next_line.c ./external/get_next_line/get_next_line_utils.c
SRCS = $(addprefix srcs/, $(SRC))
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./external/libft/
LIBFT = $(LIBFT_DIR)libft.a
PRINTF_DIR = ./external/ft_printf/
PRINTF = $(PRINTF_DIR)libftprintf.a
MLX_DIR = ./external/mlx/
MLX = $(MLX_DIR)libmlx.a
MLX_FLAG = -lXext -lX11 -lm
INCLUDES = $(LIBFT) $(PRINTF) $(MLX)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF) $(MLX)
	$(CC) $(CFLAGS) $(MLX_FLAG) $(OBJS) $(GNL) -o $(NAME) $(INCLUDES) 

learn: $(LIBFT) $(PRINTF) $(MLX)
	cc $(MLX_FLAG) ./srcs/learn_mlx.c  $(INCLUDES) 
$(LIBFT):
	make -C $(LIBFT_DIR)
$(PRINTF):
	make -C $(PRINTF_DIR)
$(MLX):
	make -C $(MLX_DIR)
clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PRINTF_DIR)
	make fclean -C $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re