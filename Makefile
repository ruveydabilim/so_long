NAME = so_long
CC = cc
CFLAGS = -g -Wall -Wextra -Werror 
SRC = main.c map_parser.c map_validation.c so_long.c map_utils.c free_all.c \
	key_utils.c init_game.c
BONUSRC = main_bonus.c map_parser_bonus.c map_validation_bonus.c so_long_bonus.c \
	map_utils_bonus.c free_all_bonus.c key_utils_bonus.c init_game_bonus.c
GNL = ./external/get_next_line/get_next_line.c ./external/get_next_line/get_next_line_utils.c
SRCS = $(addprefix srcs/, $(SRC))
BONUSRCS = $(addprefix bonus/, $(BONUSRC))
OBJS = $(SRCS:.c=.o)
BONUSOBJS = $(BONUSRCS:.c=.o)
LIBFT_DIR = ./external/libft/
LIBFT = $(LIBFT_DIR)libft.a
PRINTF_DIR = ./external/ft_printf/
PRINTF = $(PRINTF_DIR)libftprintf.a
MLX_DIR = ./external/mlx/
MLX = $(MLX_DIR)libmlx.a
MLX_FLAG = -lXext -lX11 -lm
INCLUDES = $(LIBFT) $(PRINTF) $(MLX)

all: $(NAME)

bonus: $(MLX) $(BONUSOBJS) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(BONUSOBJS) $(GNL) -o $(NAME) $(INCLUDES) $(MLX_FLAG) 

$(NAME): $(MLX) $(OBJS) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(OBJS) $(GNL) -o $(NAME) $(INCLUDES) $(MLX_FLAG)
$(LIBFT):
	make -s -C $(LIBFT_DIR)
$(PRINTF):
	make -s -C $(PRINTF_DIR)

$(MLX): mlx_install
	make -s -C $(MLX_DIR)

mlx_install:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42paris/minilibx-linux.git mlx;\
		mv mlx ./external/; fi
clean:
	@rm -f $(OBJS) $(BONUSOBJS)
	make -s clean -C $(LIBFT_DIR)
	make -s clean -C $(PRINTF_DIR)
	make -s clean -C $(MLX_DIR)

fclean: clean
	@rm -rf $(NAME)
	make -s fclean -C $(LIBFT_DIR)
	make -s fclean -C $(PRINTF_DIR)
	rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re bonus mlx_install