# Program
NAME = cub3D

# Compiler
CC = cc
#CFLAGS = -Wall -Wextra -Werror -Iincludes -g
CFLAGS = -Iincludes -g

# Directories
SRC_DIR		= src
OBJ_DIR		= objs
LIBFT_DIR	= libft

# Find all .c files
SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Minilibx
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INC = -I$(MLX_DIR)
MLXFLAGS = $(MLX_INC) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_DIR)/libft.a:
	@echo "🔗 Ligando $(NAME)..."
	$(MAKE) -C $(LIBFT_DIR)
	@echo "\033[1;45m✅ Libft compilada com sucesso!\033[0m"

$(NAME): $(MLX_LIB) $(LIBFT_DIR)/libft.a $(OBJS)
	@echo "🔗 Ligando $(NAME)..."
	$(CC) $(CFLAGS) -I$(MLX_DIR) -L$(LIBFT_DIR) -o $(NAME) $(OBJS) -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm
	@echo "\033[1;45m✅ Bola Quadrada 🟨 compilada com sucesso!\033[0m"

run: all
	valgrind --leak-check=full --show-leak-kinds=all ./cub3D ./maps/3_map_error.cub

clean:
	$(RM) -r $(OBJ_DIR) 
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) ./$(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
