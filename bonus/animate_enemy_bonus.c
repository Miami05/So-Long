/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_enemy_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:35:35 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/19 19:02:25 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	animate_enemy_sprite(t_game *game)
{
	static int	frame_counter = 0;

	if (++frame_counter >= 10)
	{
		game->enemy.current_frame = (game->enemy.current_frame + 1) % 3;
		frame_counter = 0;
	}
}

void	update_enemy_pos_2(t_game *game)
{
	static int		direction_counter = 0;

	if (++direction_counter >= 20)
	{
		game->enemy.direction = rand() % 4;
		direction_counter = 0;
	}
}

static void	update_enemy_position_utils(t_game *game, int *move_counter)
{
	int				new_x;
	int				new_y;

	new_x = game->enemy.x;
	new_y = game->enemy.y;
	update_enemy_pos_2(game);
	if (game->enemy.direction == 3)
		new_y -= 1;
	else if (game->enemy.direction == 0)
		new_y += 1;
	else if (game->enemy.direction == 1)
		new_x -= 1;
	else if (game->enemy.direction == 2)
		new_x += 1;
	if (new_y < 0 || new_y >= game->map.row || new_x < 0
		|| new_x >= game->map.col || game->map.map[new_y][new_x] == '1'
		|| game->map.map[new_y][new_x] == 'E')
	{
		game->enemy.direction = (game->enemy.direction + 1) % 4;
		move_counter = 0;
		return ;
	}
	game->enemy.x = new_x;
	game->enemy.y = new_y;
	*move_counter = 0;
}

static void	update_enemy_position(t_game *game)
{
	int				prev_x;
	int				prev_y;
	static int		move_counter = 0;

	prev_x = game->enemy.x;
	prev_y = game->enemy.y;
	if (++move_counter >= 1000)
		update_enemy_position_utils(game, &move_counter);
	if (game->enemy.x == game->player.x / TILE_SIZE
		&& game->enemy.y == game->player.y / TILE_SIZE)
	{
		error("Game Over! Caught by enemy!\n");
		exit_game(game);
	}
	if (prev_x != game->enemy.x || prev_y != game->enemy.y)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->texture.bg, prev_x
			* TILE_SIZE, prev_y * TILE_SIZE);
	}
}

void	render_enemy(t_game *game)
{
	if (!game->enemy.alive)
		return ;
	update_enemy_position(game);
	animate_enemy_sprite(game);
	mlx_put_image_to_window(game->mlx, game->win,
		game->enemy.sprites[game->enemy.direction][game->enemy.current_frame],
		game->enemy.x * TILE_SIZE, game->enemy.y * TILE_SIZE);
	render_game_stats(game);
}
