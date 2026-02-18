NAME = cub3D
FLAGS = -Wall -Wextra -Werror
SAN = -Wall -Wextra -Werror -fsanitize=address
OPTION = -MMD -c -I. -Iinc/
# Paths
LIBFT_PATH = lib/Libft

# Colors
BRED = \033[1;31m
BYEL = \033[1;33m
BGREEN = \033[1;32m
RED = \033[0;31m
YEL = \033[0;33m
GREEN = \033[0;32m
NC = \033[0m

INCLUDE = $(LIBFT_PATH)/libft.h inc/cub3D.h Makefile

# Library files
LIBFT = $(LIBFT_PATH)/libft.a

SRC = src/cub3D.c \
	src/parse.c \
	src/init.c \
	src/ft_exit.c \
	src/ft_isclosed.c

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

# Compile the final executable
all: $(NAME)

# Rebuild Libft if any object file changes
$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)


$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) $(FLAGS) $(LIBFT) -lreadline -o $(NAME)
	@echo "😃 ${BGREEN}Compiled ${BYEL}$(NAME)${NC}"

# Compile object files and generate .d files for dependencies
%.o: %.c $(INCLUDE)
	@cc $(FLAGS) $(OPTION) $< -o $@

# Include the generated dependency files
-include $(DEP)

# Clean object and dependency files
clean:
	@/bin/rm -f $(OBJ) $(DEP)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@echo "🗑️  $(BRED)Removed $(YEL)$(OBJ)${NC}"

# Full clean
fclean:
	@/bin/rm -f $(OBJ) $(DEP)
	@echo "🗑️  $(BRED)Removed $(YEL)$(OBJ)${NC}"
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@/bin/rm -f $(NAME)
	@echo "🗑️  $(BRED)Removed $(BYEL)$(NAME)${NC}"

# Rebuild everything
re: fclean all

san:
	@$(CC) $(OBJ) $(SAN) $(LIBFT) -o $(NAME)
	@echo "😃 ${BGREEN}Compiled (sanitize) ${BYEL}$(NAME)${NC}"

.PHONY: all, clean, fclean, re
