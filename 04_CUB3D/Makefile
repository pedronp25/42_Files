CC = cc -g
AR = ar rcs
RM = rm -f

NAME = cub3d
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT_NAME = libft_printf.a
LIBFT = $(LIBFT_DIR)/$(LIBFT_NAME)

MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a

SRC_DIR = .
OBJ_DIR = objs

SRCS = cub3d.c \
	   cbd_validate_initialize.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

DEPS = cub3d.h $(LIBFT_DIR)/libft.h $(MLX_DIR)/mlx.h

all: $(LIBFT) $(MLX_LIB) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) -o $(NAME) -lXext -lX11 -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean
	$(RM) $(NAME)

re: fclean all
