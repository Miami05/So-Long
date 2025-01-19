/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_bomb_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:13:02 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/17 21:13:18 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	place_bomb_utils(t_game *game, int grid_x, int grid_y)
{
	if (!game->bomb.active && (game->map.map[grid_y][grid_x] == '0'
		|| game->map.map[grid_y][grid_x] == BOMB_ACTIVE))
	{
		game->bomb.x = grid_x * TILE_SIZE;
		game->bomb.y = grid_y * TILE_SIZE;
		game->bomb.active = 1;
		game->bomb.timer = 6500;
		game->bomb.current_frame = 0;
		game->bomb.is_exploding = false;
		game->map.map[grid_y][grid_x] = BOMB_ACTIVE;
		mlx_put_image_to_window(game->mlx, game->win, game->texture.bg,
			game->bomb.x, game->bomb.y);
		if (game->bomb.sprites)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->bomb.sprites,
				game->bomb.x, game->bomb.y);
			mlx_do_sync(game->mlx);
		}
	}
}

void	place_bomb(t_game *game)
{
	int	grid_x;
	int	grid_y;
	int	old_x;
	int	old_y;

	grid_x = game->player.x / TILE_SIZE;
	grid_y = game->player.y / TILE_SIZE;
	old_x = game->bomb.x / TILE_SIZE;
	old_y = game->bomb.y / TILE_SIZE;
	if (game->bomb.active && (old_x != grid_x || old_y != grid_y))
	{
		game->map.map[old_y][old_x] = '0';
		mlx_put_image_to_window(game->mlx, game->win, game->texture.bg, old_x
			* TILE_SIZE, old_y * TILE_SIZE);
	}
	place_bomb_utils(game, grid_x, grid_y);
}

void	bomb_exploding(t_game *game)
{
	if (!game->bomb.is_exploding)
		return ;
	clear_explosion_area(game);
	render_explosion(game);
	if (game->bomb.explosion_duration > 0)
	{
		game->bomb.explosion_duration--;
		if (game->bomb.explosion_duration % 30 == 0)
		{
			game->bomb.explosion_frame = (game->bomb.explosion_frame + 1) % 4;
			clear_explosion_area(game);
			render_explosion(game);
		}
	}
	else
	{
		clear_explosion_area(game);
		game->bomb.active = 0;
		game->bomb.is_exploding = false;
		game->map.map[game->bomb.y / TILE_SIZE][game->bomb.x / TILE_SIZE] = '0';
		mlx_put_image_to_window(game->mlx, game->win, game->texture.bg,
			game->bomb.x, game->bomb.y);
	}
}

static void	update_bomb_state_utils(t_game *game)
{
	if (game->bomb.timer > 0)
	{
		game->bomb.timer--;
		if (game->bomb.timer % 20 == 0)
		{
			game->bomb.current_frame = (game->bomb.current_frame + 1) % 4;
			mlx_put_image_to_window(game->mlx, game->win, game->texture.bg,
				game->bomb.x, game->bomb.y);
			mlx_put_image_to_window(game->mlx, game->win, game->bomb.sprites,
				game->bomb.x, game->bomb.y);
		}
	}
	else
	{
		game->bomb.is_exploding = true;
		game->bomb.explosion_frame = 0;
		game->bomb.explosion_duration = 400;
		game->bomb.explosion_radius = game->player.bomb_power;
	}
}

void	update_bomb_state(t_game *game)
{
	if (!game->bomb.active)
		return ;
	if (!game->bomb.is_exploding)
		update_bomb_state_utils(game);
	else
		bomb_exploding(game);
}
