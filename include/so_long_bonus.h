/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:27:40 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/18 14:55:33 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS
# define SO_LONG_BONUS

# include "so_long.h"

void		init_enemy(t_game *game);
void		load_enemy(t_game *game);
void		free_enemy_sprite(t_game *game);
void	    update_enemy(t_game *game);
void        setup_game_tools(t_game *game);
void        render_enemy(t_game *game);
void        init_enemy_map(t_game *game);
void		render_bomb(t_game *game);
void		update_bomb_state(t_game *game);
void        render_explosion(t_game *game);
void        place_bomb(t_game *game);
void        free_bomb(t_game *game);
void        init_bomb(t_game *game);
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
void		init_bomb(t_game *game);
void		reset_player(t_game *game);
int			game_loop(t_game *game);
void		render_bomb(t_game *game);
void		cleanup_player_sprites(t_game *game);
void		clear_explosion_area(t_game *game);
void		free_bomb(t_game *game);
void		free_box(t_game *game);
void		free_textures(t_game *game);
void		free_collectible_coins(t_game *game);
void		free_bomb(t_game *game);
void		free_map(t_game *game);
bool		is_map_valid_size(t_game *game);
bool		valid_map_character(t_game *game);
void        render_game_stats(t_game *game);
void        load_player_utils(t_game *game, const char *sprites_path[4][3]);

#endif