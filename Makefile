NAME = cub3D
FLAGS = -Wall -Wextra -Werror -lmlx \
	-L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -lbsd
CFLAGS = -Wall -Wextra -Werror -Ilib/minilibx-linux
LDFLAGS = -Llib/minilibx-linux
LDLIBS = -lmlx -lXext -lX11 -lm -lz -lbsd
SAN = $(FLAGS) -fsanitize=address
OPTION = -MMD -c -I. -Iinc/
# Paths
LIBFT_PATH = lib/Libft
MINILIBX_PATH = lib/minilibx-linux

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

MINILIBX = $(MINILIBX_PATH)/libmlx.a

SRC = src/cub3D.c \
	src/parse.c \
	src/parse_utils.c \
	src/parse_rgb.c \
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

$(MINILIBX):
	$(MAKE) -C $(MINILIBX_PATH)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) $(LIBFT) $(MINILIBX) -o $(NAME)
	@echo "😃 ${BGREEN}Compiled ${BYEL}$(NAME)${NC}"

# Compile object files and generate .d files for dependencies
%.o: %.c $(INCLUDE)
	@cc $(CFLAGS) $(OPTION)  $< -o $@

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
	@$(MAKE) -C $(MINILIBX_PATH) clean
	@/bin/rm -f $(NAME)
	@echo "🗑️  $(BRED)Removed $(BYEL)$(NAME)${NC}"

# Rebuild everything
re: fclean all

san:
	@$(CC) $(OBJ) $(SAN) $(LIBFT) -o $(NAME)
	@echo "😃 ${BGREEN}Compiled (sanitize) ${BYEL}$(NAME)${NC}"

.PHONY: all, clean, fclean, re
