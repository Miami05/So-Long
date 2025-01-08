/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:20:01 by ledio             #+#    #+#             */
/*   Updated: 2024/12/24 20:40:59 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include "../libft/include/libft.h"
# include <math.h>
# include <stdbool.h>

# define TILE_SIZE 32
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_SPACE 32
# define BOMB_ACTIVE '4'

typedef struct s_coins
{
	void	*sprites[9];
	int		width;
	int		height;
	int		current_frame;
	int		anim_speed;
}	t_coins;

typedef struct s_box
{
	void	*sprites;
	int		width;
	int		height;
}	t_box;

typedef struct s_moves
{
	int		x;
	int		y;
	int		grid_x;
	int		grid_y;
	int		new_grid_x;
	int		new_grid_y;
	int		center_x;
	int		center_y;
	int		current_x;
	int		current_y;
}	t_moves;

typedef struct s_enemy
{
	int		x;
	int		y;
	int		width;
	int		height;
	void	*sprites[4][3];
	int		direction;
	int		current_frame;
	int		alive;
}	t_enemy;

typedef struct s_map
{
	int		row;
	int		col;
	char	**map;
	int		collectible;
	int		player;
	int		exit;
}			t_map;

typedef struct s_texture
{
	void	*wall;
	void	*bg;
	void	*exit_sprites[2];
	int		exit_state;
}	t_texture;

typedef struct s_bomb
{
	int		x;
	int		y;
	void	*sprites;
	void	*explosion_sprites[4];
	int		current_frame;
	int		explosion_frame;
	int		timer;
	int		active;
	int		width;
	int		height;
	bool	is_exploding;
	int		explosion_radius;
	int		explosion_duration;
}	t_bomb;

typedef struct s_player
{
	int			x;
	int			y;
	int			moves;
	int			direction;
	void		*sprites[4][3];
	int			current_frame;
	int			width;
	int			height;
	int			frame_count;
	bool		is_moving;
	int			prev_x;
	int			prev_y;
	int			max_coins;
	int			collected_coins;
	int			explosion_power;
	int			bomb_power;
	int			coins_needed;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_texture	texture;
	t_player	player;
	t_bomb		bomb;
	t_moves		moves;
	t_enemy		enemy;
	t_box		box;
	t_coins		coins;
	int			width;
	int			height;
	int			i;
}	t_game;

void		load_map(char *filename, t_game *game);
int			error(char *message);
void		load_texture(t_game *game);
void		init_vars(t_game *game);
bool		has_required_elements(t_game *game);
void		free_map_copy(char **map_copy, t_game *game);
bool		validate_map(t_game *game);
bool		is_path_valid(t_game *game);
int			key_press(int keycode, t_game *game);
void		setup_game_tools(t_game *game);
bool		is_valid_move(t_game *game, int grid_x, int grid_y);
void		move_player(t_game *game, int new_grid_x, int new_grid_y);
void		exit_game(t_game *game);
void		animate_player(t_game *game);
int			key_release(int keycode, t_game *game);
void		init_player(t_game *game);
int			render_map(t_game *game);
void		load_sprites(t_game *game);
void		place_bomb(t_game *game);
void		animate_coin(t_game *game);
void		render_explosion(t_game *game);
void		update_bomb_state(t_game *game);

#endif