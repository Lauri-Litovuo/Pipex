NAME = pipex
BNAME = pipex_bonus

LIBFT = libft/libft.a

S = srcs/
O = objs/
I = incl/
L = libft/
B = bonus/

all: $(NAME)

bonus: $(BNAME)

libft: $(LIBFT)

.PHONY: all clean fclean re bonus

CC = cc
CFLAGS += -Wall -Wextra -Werror -I$I
LDFLAGS += 

#MANDATORY

SRC = \
		$Spipex.c \
		$Spipex_utils.c \
		$Scmds_handling.c \
		$Sfree_functions.c \
		$Spaths_handling.c \
		$Spiping.c \
		
OBJ = $(SRC:$S%=$O%.o)

$O:
	@mkdir -p $@
	@echo "Making obj dir and files.."

$(OBJ): | $O

$O%.o: $S% $(LIBFT)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "Project ready for use."

#BONUS

SRC_B = \
		$Bpipex_bonus.c \
		$Bpipex_utils_bonus.c \
		$Bcmds_handling_bonus.c \
		$Bfree_functions_bonus.c \
		$Bpaths_handling_bonus.c \
		$Bpiping_bonus.c \

OBJ_B = $(SRC_B:$B%=$O%.o)

$(OBJ_B): | $O

$O%bonus.c.o: $B% $(LIBFT)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BNAME): $(LIBFT) $(OBJ_B)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "Project ready for use."

#DEBUG

DEBUG_NAME = debug.out

debug: $(DEBUG_NAME)

DEBUG_FLAGS = -g -fsanitize=address,undefined,integer

$(DEBUG_NAME): $(LIBFT) $(OBJ)
	@$(CC) $(DEBUG_FLAGS) $^ -o $@
	@echo "Debug ready for use."

cleandebug: fclean
	@rm -f $(DEBUG_NAME)
	@echo "debug.out removed"

#LIBFT

$(LIBFT): $L
	@make -C $L

cleanobj:
	@rm -f $(wildcard $(OBJ))

cleanobjdir: cleanobj
	@rm -rf $O

cleanlibft:
	@make fclean -C $L

clean: cleanobjdir cleanlibft
	@echo "Cleaning object files and libft"

fclean: clean
	@rm -f $(NAME) $(BNAME)
	@echo "Project file removed"

re: fclean all