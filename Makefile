# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 18:25:22 by ledio             #+#    #+#              #
#    Updated: 2025/01/20 13:13:46 by ldurmish         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name
NAME = so_long
BONUS_NAME = so_long_bonus

# Compiler setting
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -Lminilibx-linux/ -lmlx_Linux -L/usr/lib/X11 -lXext -lX11
INCLUDE = -I include -I libft/include -I/libft/ft_printf/include -I/usr/include
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(LIBFT_DIR)/libftprintf.a
BONUS = bonus/
SRC = src/

# Color codes
RESET = \033[0m
GREEN = \033[0;32m
RED = \033[0;31m

# Source files for so_long
SRCS = $(SRC)animate_player.c $(SRC)errors.c $(SRC)game_utils.c \
		$(SRC)main_utils_3.c $(SRC)main_utils_2.c $(SRC)main_utils.c \
		$(SRC)map_utils.c $(SRC)so_long.c $(SRC)texture_utils.c $(SRC)texture_utils_2.c \
		$(SRC)render_textures.c $(SRC)errors_2.c $(SRC)utils.c\

BONUS_SRCS = $(BONUS)animate_enemy_bonus.c $(BONUS)utils_bonus.c $(BONUS)so_long_bonus.c \
				$(BONUS)texture_utils_bonus.c $(BONUS)utils_3_bonus.c $(BONUS)main_utils_bonus.c \
				$(BONUS)render_texture_bonus.c $(BONUS)animate_player_bonus.c $(BONUS)errors_bonus.c \
				$(BONUS)game_utils_bonus.c $(BONUS)main_utils_1_bonus.c $(BONUS)main_utils_2_bonus.c \
				$(BONUS)map_utils_bonus.c $(BONUS)texture_utils_2_bonus.c $(BONUS)animate_bomb_bonus.c \
				$(BONUS)explosion_bomb_bonus.c $(BONUS)errors_2_bonus.c $(BONUS)utils_2_bonus.c \
				$(BONUS)animate_player_utils_bonus.c $(BONUS) utils_1_bonus.c\

# Object files
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# Main target
all: $(LIBFT) $(NAME) $(FT_PRINTF)

# Compiling libft
$(LIBFT):
		@echo "$(GREEN)Compiling libft...$(RESET)"
		@$(MAKE) -C $(LIBFT_DIR)
		@echo "$(GREEN)libft compiled successfully!$(RESET)"

# Compile so_long
$(NAME):$(OBJS)
		@echo "$(GREEN)Compiling so_long...$(RESET)"
		$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -L$(LIBFT_DIR) -lftprintf -lft $(MLX_FLAGS) -o $(NAME)
		@echo "$(GREEN)so_long compiled successfully!$(RESET)"

# Compile source files to object files
%.o:%.c
		$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Bonus target
bonus: $(LIBFT) $(BONUS_OBJS)
		@echo "$(GREEN)Compiling so_long bonus...$(RESET)"
		$(CC) $(CFLAGS) $(INCLUDE) $(BONUS_OBJS) -L$(LIBFT_DIR) -lftprintf -lft $(MLX_FLAGS) -o $(BONUS_NAME)
		@echo "$(GREEN)so_long bonus compiled successfully!$(RESET)"

# Clean object files and executables
clean:
		@echo "$(RED)Cleaning object files...$(RESET)"
		@rm -f $(OBJS) $(BONUS_OBJS)
		@$(MAKE) -C $(LIBFT_DIR) clean
		@echo "$(GREEN)Object files cleaned successfully!$(RESET)";

# Removing all (including executables)
fclean: clean
		@echo "$(RED)Cleaning executables...$(RESET)"
		@rm -f $(NAME) $(BONUS_NAME)
		@$(MAKE) -C $(LIBFT_DIR) fclean
		@echo "$(GREEN)Executables cleaned successfully!$(RESET)"

# Rebuild the project
re: fclean all

# Phony targets
.PHONY: all clean fclean re bonus