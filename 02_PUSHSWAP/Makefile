CC = cc
AR = ar rcs
RM = rm -f

NAME = push_swap
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)/$(LIBFT_NAME)

PUSH_SWAP_SRCS = push_swap.c

PUSH_SWAP_OBJDIR = push_swap_objs
PUSH_SWAP_OBJS = $(PUSH_SWAP_SRCS:%.c=$(PUSH_SWAP_OBJDIR)/%.o)

DEPS = push_swap.h $(LIBFT_DIR)/libft.h

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(PUSH_SWAP_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(PUSH_SWAP_OBJS) $(LIBFT) -o $(NAME)

$(PUSH_SWAP_OBJDIR)/%.o: %.c $(DEPS)
	@mkdir -p $(PUSH_SWAP_OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(PUSH_SWAP_OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all
