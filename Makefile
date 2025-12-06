# Program
NAME = cub3D

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft_utils -g

# Directories
SRC_DIR			= src
OBJ_DIR			= objs
LIBFT_UTILS_DIR	= libft_utils

# Source files
SRCS = $(SRC_DIR)/03_controls/rotation.c \
       $(SRC_DIR)/03_controls/hooks.c \
       $(SRC_DIR)/03_controls/movement.c \
       $(SRC_DIR)/free.c \
       $(SRC_DIR)/02_engine/player_init.c \
       $(SRC_DIR)/02_engine/render_frame.c \
       $(SRC_DIR)/02_engine/engine_management.c \
       $(SRC_DIR)/02_engine/raycasting.c \
       $(SRC_DIR)/main.c \
       $(SRC_DIR)/utils/pixel_utils.c \
       $(SRC_DIR)/utils/raycasting_utils.c \
       $(SRC_DIR)/utils/signal_handler.c \
       $(SRC_DIR)/utils/raycasting_draw.c \
       $(SRC_DIR)/01_parsing/00parsing.c \
       $(SRC_DIR)/01_parsing/05_mlx.c \
       $(SRC_DIR)/01_parsing/03_map.c \
       $(SRC_DIR)/01_parsing/06error.c \
       $(SRC_DIR)/01_parsing/01lexer.c \
       $(SRC_DIR)/01_parsing/02aux.c \
       $(SRC_DIR)/01_parsing/04_elements.c

LIBFT_UTILS_SRCS = $(LIBFT_UTILS_DIR)/ft_strncmp.c \
                   $(LIBFT_UTILS_DIR)/ft_strtrim.c \
                   $(LIBFT_UTILS_DIR)/ft_printf_utils.c \
                   $(LIBFT_UTILS_DIR)/ft_split.c \
                   $(LIBFT_UTILS_DIR)/ft_string_utils.c \
                   $(LIBFT_UTILS_DIR)/ft_substr.c \
                   $(LIBFT_UTILS_DIR)/get_next_line.c \
                   $(LIBFT_UTILS_DIR)/get_next_line_utils.c \
                   $(LIBFT_UTILS_DIR)/ft_strrchr.c \
                   $(LIBFT_UTILS_DIR)/ft_atoi.c \
                   $(LIBFT_UTILS_DIR)/ft_printf_hex.c \
                   $(LIBFT_UTILS_DIR)/ft_printf.c \
                   $(LIBFT_UTILS_DIR)/ft_isdigit.c

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
LIBFT_UTILS_OBJS = $(patsubst $(LIBFT_UTILS_DIR)/%.c, $(OBJ_DIR)/libft_utils/%.o, $(LIBFT_UTILS_SRCS))

# Minilibx
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INC = -I$(MLX_DIR)
MLXFLAGS = $(MLX_INC) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/libft_utils/%.o: $(LIBFT_UTILS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(LIBFT_UTILS_DIR) -c $< -o $@

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(MLX_LIB) $(OBJS) $(LIBFT_UTILS_OBJS)
	@echo "🔗 Ligando $(NAME)..."
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_UTILS_DIR) -o $(NAME) $(OBJS) $(LIBFT_UTILS_OBJS) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
	@echo "\033[1;45m✅ Bola Quadrada 🟨 compilada com sucesso!\033[0m"

run: all
	./cub3D ./maps/maps_valid/21c-valid_file_map.cub

val: all
	valgrind --suppressions=valgrind.supp --leak-check=full --show-leak-kinds=all ./cub3D ./maps/maps_valid/21b-valid_file_map.cub

valgrind-full: all
	valgrind --leak-check=full --show-leak-kinds=all ./cub3D ./maps/maps_valid/21c-valid_file_map.cub

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) ./$(NAME)

re: fclean all

.PHONY: all run valgrind valgrind-full clean fclean re
