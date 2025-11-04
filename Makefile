NAME = so_long
CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror
SRC = main.c map_parser.c map_validation.c so_long.c map_utils.c free_all.c \
	key_utils.c
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

$(NAME): $(MLX) $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(GNL) -o $(NAME) $(INCLUDES) $(MLX_FLAG) 
$(LIBFT):
	make -C $(LIBFT_DIR)
$(PRINTF):
	make -C $(PRINTF_DIR)

$(MLX): mlx_install
	make -C $(MLX_DIR)

mlx_install:
	if [ ! -d "$(MLX_DIR)" ]; then \
		wget https://cdn.intra.42.fr/document/document/40310/minilibx-linux.tgz; \
		tar -xzvf minilibx-linux.tgz; \
		mv minilibx-linux $(MLX_DIR); \
		rm -rf minilibx-linux.tgz; fi
clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re mlx_install