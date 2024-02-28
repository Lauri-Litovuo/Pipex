NAME = libft.a

all: $(NAME)

SOURCES = ft_isascii.c \
			ft_memcpy.c \
			ft_strlen.c \
			ft_tolower.c \
			ft_atoi.c \
			ft_isdigit.c \
			ft_memmove.c \
			ft_putstr_fd.c \
			ft_strncmp.c \
			ft_toupper.c \
			ft_bzero.c \
			ft_isprint.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strnstr.c \
			ft_isalnum.c \
			ft_memchr.c \
			ft_putchar_fd.c \
			ft_strlcat.c \
			ft_strrchr.c \
			ft_isalpha.c \
			ft_memcmp.c \
			ft_putendl_fd.c \
			ft_strlcpy.c \
			ft_putnbr_fd.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_itoa.c	\
			ft_split.c	\
			ft_lstadd_front.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			./ft_printf/ft_printf.c \
			./ft_printf/ft_putchar.c \
			./ft_printf/ft_putstr.c	\
			./ft_printf/ft_putnbr_base.c \
			./ft_printf/ft_putptr.c \
			./get_next_line/get_next_line.c \
			./get_next_line/get_next_line_utils.c \

OBJECTS = $(SOURCES:.c=.o)

HEADERS = libft.h

CC: cc

CFLAGS = -g -Wall -Wextra -Werror

$(NAME): $(OBJECTS)
	@ar -rsc $(NAME) $(OBJECTS)
	@echo "Libft making in progress..."

%.o: %.c
	@cc $(CFLAGS) -c $< -o $@ -I $(HEADERS)

clean:
	@rm -f $(OBJECTS)
	@echo "Removing .o files"

fclean: clean
	@rm -f $(NAME)
	@echo "Removing libft.a"

re: fclean all

.PHONY: all clean fclean re
