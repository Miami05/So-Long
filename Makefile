# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ledio <ledio@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 18:25:22 by ledio             #+#    #+#              #
#    Updated: 2024/12/23 23:47:04 by ledio            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name
NAME = so_long

# Compiler setting
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -Lminilibx-linux/ -lmlx_Linux -L/usr/lib/X11 -lXext -lX11
INCLUDE = -I include -I libft/include -I/libft/ft_printf/include -I/usr/include
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(LIBFT_DIR)/libftprintf.a

# Color codes
RESET = \033[0m
GREEN = \033[0;32m
RED = \033[0;31m

# Soure files for so_long
SRCS = animate_player.c errors.c game_utils.c \
		main_utils_3.c main_utils_2.c main_utils.c \
		map_utils.c so_long.c texture_utils.c texture_utils_2.c \
		animate_bomb.c render_textures.c \

# Object files
OBJS = $(SRCS:.c=.o)

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
		$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lftprintf -lft -o $(NAME)
		@echo "$(GREEN)so_long compiled successfully!$(RESET)"

# Compile source files to object files
%.o:%.c
		$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Clean object files and executables
clean:
		@echo "$(RED)Cleaning object files...$(RESET)"
		@rm -f $(OBJS)
		@$(MAKE) -C $(LIBFT_DIR) clean
		@echo "$(GREEN)Object files cleaned successfully!$(RESET)";

# Removing all (including executables)
fclean: clean
		@echo "$(RED)Cleaning executables...$(RESET)"
		@rm -f $(NAME)
		@$(MAKE) -C $(LIBFT_DIR) fclean
		@echo "$(GREEN)Executables cleaned successfully!$(RESET)"

# Rebuild the project
re: fclean all

# Phony targets
.PHONY: all clean fclean re