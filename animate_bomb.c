/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_bomb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 23:46:30 by ledio             #+#    #+#             */
/*   Updated: 2024/12/24 20:40:39 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_bomb_state(t_game *game)
{
	if (game->bomb.active)
	{
		if (!game->bomb.is_exploding)
		{
			game->bomb.current_frame = (game->bomb.current_frame + 1) % 1;
			mlx_put_image_to_window(game->mlx, game->win,
				game->bomb.sprites, game->bomb.x, game->bomb.y);
			game->bomb.timer--;
			if (game->bomb.timer <= 0)
			{
				game->bomb.is_exploding = true;
				game->bomb.explosion_frame = 0;
			}
		}
		else
		{
			render_explosion(game);
			game->bomb.explosion_duration--;
			if (game->bomb.explosion_duration % 8 == 0)
				game->bomb.explosion_duration
					= (game->bomb.explosion_duration + 1) % 4;
			if (game->bomb.explosion_duration <= 0)
			{
				game->bomb.active = 0;
				game->bomb.is_exploding = false;
			}
		}
	}
}

void	place_bomb(t_game *game)
{
	int		grid_x;
	int		grid_y;

	grid_x = game->player.x / TILE_SIZE;
	grid_y = game->player.y / TILE_SIZE;
	if (!game->bomb.active && game->map.map[grid_y][grid_x] == '0')
	{
		game->bomb.x = grid_x * TILE_SIZE;
		game->bomb.y = grid_y * TILE_SIZE;
		game->bomb.active = 1;
		game->bomb.timer = 120;
		game->bomb.is_exploding = false;
		game->bomb.current_frame = 0;
		game->bomb.explosion_duration = 45;
		game->bomb.explosion_frame = 0;
		game->bomb.explosion_radius = game->player.bomb_power;
		mlx_put_image_to_window(game->mlx, game->win,
			game->bomb.sprites, game->bomb.x, game->bomb.y);
		game->map.map[grid_y][grid_x] = BOMB_ACTIVE;
	}
}

void	handle_box_destruction(t_game *game, int grid_x, int grid_y)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->texture.bg, grid_x * TILE_SIZE, grid_y * TILE_SIZE);
	if (game->map.map[grid_y][grid_x] == 'B')
		game->map.map[grid_y][grid_x] = '0';
	else if (game->map.map[grid_y][grid_x] == '3')
	{
		game->map.map[grid_y][grid_x] = 'C';
		game->map.map[grid_y][grid_x] = '0';
		game->map.collectible++;
		mlx_put_image_to_window(game->mlx, game->win,
			game->coins.sprites[game->coins.current_frame],
			grid_x * TILE_SIZE, grid_y * TILE_SIZE);
	}
}

void	render_explosion_utils(t_game *game, int current_x, int current_y)
{
	if (current_x >= 0 && current_x < game->map.col
		&& current_y >= 0 && current_y < game->map.row
		&& game->map.map[current_y][current_x] != '1')
	{
		if (game->bomb.explosion_sprites[game->bomb.explosion_frame])
		{
			mlx_put_image_to_window(game->mlx, game->win,
				game->bomb.explosion_sprites[game->bomb.explosion_frame],
				current_x * TILE_SIZE, current_y * TILE_SIZE);
			if (game->map.map[current_y][current_x] == 'B'
				|| game->map.map[current_y][current_x] == '3')
				handle_box_destruction(game, current_x, current_y);
		}
	}
}

void	render_explosion(t_game *game)
{
	int		radius;
	int		dx;
	int		dy;

	radius = game->bomb.explosion_radius;
	game->moves.center_x = game->bomb.x / TILE_SIZE;
	game->moves.center_y = game->bomb.y / TILE_SIZE;
	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			game->moves.current_x = game->moves.center_x + dx;
			game->moves.current_y = game->moves.center_y + dy;
			render_explosion_utils(game, game->moves.current_x,
				game->moves.current_y);
			dx++;
		}
		dy++;
	}
}
