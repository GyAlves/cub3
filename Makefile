# Program
NAME = bola_quadrada

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

# Directories
SRC_DIR = src/
OBJ_DIR = objs/

# Find all .c files
SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")

OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

# Minilibx
MLX_DIR = mlx_linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INC = -I$(MLX_DIR)
MLXFLAGS = $(MLX_INC) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -o $(NAME) $(OBJS) $(MLX_LIB) $(MLXFLAGS)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) ./$(NAME)

re: fclean all

.PHONY: all clean fclean re
