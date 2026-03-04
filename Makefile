# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexp <alexp@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/22 17:41:17 by sarodrig          #+#    #+#              #
#    Updated: 2026/03/04 14:40:15 by alexp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# #### DEFINES ####
BRED			= \e[1;31m
BYEL			= \e[1;33m
BGREEN			= \e[1;32m
RED				= \e[0;31m
YEL				= \e[0;33m
GREEN			= \e[0;32m
NC				= \e[0m

# #### VARIABLES ####
NAME			= cub3D

FLAGS			= -Wall -Wextra -Werror -lmlx \
				  -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -lbsd -O2
CFLAGS			= -Wall -Wextra -Werror -Ilib/minilibx-linux
LDFLAGS			= -Llib/minilibx-linux
LDLIBS			= -lmlx -lXext -lX11 -lm -lz -lbsd
OPTIONS			= -MMD -c -I. -Iinc/
SAN				= $(FLAGS) -fsanitize=address

# Dirs
SRC_DIR			= src/
INC_DIR			= inc/
OBJ_DIR			= obj/
LIBFT_DIR		= lib/Libft/
MINILIBX_DIR	= lib/minilibx-linux/

# Library binaries
LIBFT			= $(LIBFT_DIR)libft.a
MINILIBX		= $(MINILIBX_DIR)libmlx.a

# Project headers, sources, objects, and dependencies
INC				= $(INC_DIR)cub3D.h $(LIBFT_DIR)libft.h

SRC				= cub3D.c \
				  parse.c \
				  parse_utils.c \
				  parse_rgb.c \
				  parse_map.c \
				  parse_map_utils.c \
				  init.c \
				  ft_paintscreen.c \
				  ft_paintscreen_utils.c \
				  ray.c \
				  ray_utils.c \
				  ft_exit.c \
				  hooks.c \
				  hooks_utils.c \
				  textures.c \
				  parse_textures.c

OBJ 			= $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))
DEP 			= $(OBJ:.o=.d)

# #### FILE TARGETS ####
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MINILIBX):
	@$(MAKE) -C $(MINILIBX_DIR)

# Compile object files and generate .d files for dependencies
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC) Makefile
	@mkdir -p $(OBJ_DIR)
	@cc $(CFLAGS) $(OPTIONS) $< -o $@

# Include the generated dependency files
-include $(DEP)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) $(LIBFT) $(MINILIBX) -o $(NAME)
	@echo "😃 ${BGREEN}Compiled ${BYEL}$(NAME)${NC}"

# #### PHONY TARGETS ####
.PHONY: all, clean, fclean, re
.DEFAULT_GOAL = all

all: $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@/bin/rm -rf $(OBJ_DIR)
	@echo "🗑️  $(BRED)Removed $(YEL)$(OBJ)${NC}"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MINILIBX_DIR) clean
	@/bin/rm -f $(NAME)
	@echo "🗑️  $(BRED)Removed $(BYEL)$(NAME)${NC}"

re: fclean all

# #### TEST TARGETS ####
san: $(LIBFT) $(MINILIBX) $(OBJ)
	@$(CC) $(OBJ) $(SAN) $(LDFLAGS) $(LDLIBS) $(LIBFT) $(MINILIBX) -o $(NAME)
	@echo "😃 ${BGREEN}Compiled (sanitize) ${BYEL}$(NAME)${NC}"

test: san
	@./$(NAME) map/map.cub
