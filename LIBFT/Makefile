CC = cc

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_isalnum.c \
       ft_isalpha.c \
       ft_isascii.c \
       ft_isdigit.c \
       ft_isprint.c \
       ft_putchar_fd.c \
       ft_putendl_fd.c \
       ft_putstr_fd.c \
       ft_strchr.c \
       ft_strlcpy.c \
       ft_strlen.c \
       ft_strncmp.c \
       ft_strrchr.c \
       ft_tolower.c \
       ft_toupper.c \
       ft_strlcpy.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

