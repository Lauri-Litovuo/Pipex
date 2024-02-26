NAME = pipex
BNAME = pipex_bonus

LIBFT = libft/libft.a

S = srcs/
O = objs/
I = incl/
L = libft/
B = bonus/
BO = bonus_objs/

all: $(NAME)

bonus: $(BNAME)

libft: $(LIBFT)

.PHONY: all clean fclean re bonus

CC = cc
CFLAGS += -Wall -Wextra -Werror -I$I -I$L
LDFLAGS += 

##		MANDATORY 	##

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

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "Project ready for use."

##		BONUS		##

SRC_B = \
		$Bpipex_bonus.c \
		$Bpipex_utils_bonus.c \
		$Bcmds_handling_bonus.c \
		$Bfree_functions_bonus.c \
		$Bpaths_handling_bonus.c \
		$Bpiping_bonus.c \

OBJ_B = $(SRC_B:$B%=$(BO)%.o)

$(BO):
	@mkdir -p $@
	@echo "Making obj dir and files.."

$(OBJ_B): | $(BO)

$(BO)%.o: $B% $(LIBFT)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BNAME): $(OBJ_B) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "Bonus ready for use."

#DEBUG Check why this is not working properly!

DEBUG_NAME = debug.out

debug: $(DEBUG_NAME)

DEBUG_FLAGS = -g -fsanitize=address,undefined,integer

$(DEBUG_NAME): $(OBJ) $(LIBFT)
	@$(CC) $(DEBUG_FLAGS) $(CFLAGS) $^ -o $@
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

cleanbonus:
	@rm -f $(wildcard $(OBJ_B))

cleanobjbdir: cleanbonus
	@rm -rf $(BO)

cleanlibft:
	@make fclean -C $L

clean: cleanobjdir cleanlibft cleanobjbdir
	@echo "Cleaning object files and libft"

fclean: clean
	@rm -f $(NAME) $(BNAME)
	@echo "Project file removed"

re: fclean all