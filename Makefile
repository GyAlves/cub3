# Program
NAME = cub3D

# Compiler
CC = cc
#CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft_utils -g
CFLAGS = -Iincludes -Ilibft_utils -g

# Directories
SRC_DIR			= src
OBJ_DIR			= objs
LIBFT_UTILS_DIR	= libft_utils

# Find all .c files
SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")
LIBFT_UTILS_SRCS = $(shell find $(LIBFT_UTILS_DIR) -type f -name "*.c")

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
	valgrind --suppressions=valgrind.supp --leak-check=full --show-leak-kinds=all ./cub3D ./maps/maps_valid/21c-valid_file_map.cub

valgrind-full: all
	valgrind --leak-check=full --show-leak-kinds=all ./cub3D ./maps/maps_valid/21c-valid_file_map.cub

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) ./$(NAME)

re: fclean all

.PHONY: all run valgrind valgrind-full clean fclean re
