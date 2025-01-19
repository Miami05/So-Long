/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:56:32 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/18 19:50:19 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	render_map_utils(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	i = game->player.prev_y / TILE_SIZE;
	j = game->player.prev_x / TILE_SIZE;
	if (game->map.map[i][j] != '1')
		mlx_put_image_to_window(game->mlx, game->win, game->texture.bg,
			game->player.prev_x, game->player.prev_y);
	else
		mlx_put_image_to_window(game->mlx, game->win,
			game->texture.wall, game->player.prev_x, game->player.prev_y);
}

static void	render_map_texture(t_game *game, int j)
{
	mlx_put_image_to_window(game->mlx, game->win, game->texture.bg,
		j * TILE_SIZE, game->i * TILE_SIZE);
	if (game->map.map[game->i][j] == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->texture.wall, j * TILE_SIZE, game->i * TILE_SIZE);
	else if (game->map.map[game->i][j] == 'B'
		|| game->map.map[game->i][j] == '3')
		mlx_put_image_to_window(game->mlx, game->win,
			game->box.sprites, j * TILE_SIZE, game->i * TILE_SIZE);
	else if (game->map.map[game->i][j] == 'E')
	{
		if (game->player.collected_coins >= game->player.coins_needed)
			mlx_put_image_to_window(game->mlx, game->win,
				game->texture.exit_door, j * TILE_SIZE, game->i * TILE_SIZE);
		mlx_put_image_to_window(game->mlx, game->win,
			game->texture.door, j * TILE_SIZE, game->i * TILE_SIZE);
	}
}

void	render_bomb(t_game *game)
{
	int		bomb_grid_x;
	int		bomb_grid_y;

	if (game->player.prev_x != game->player.x
		|| game->player.prev_y != game->player.y)
	{
		render_map_utils(game);
	}
	if (game->bomb.active)
	{
		bomb_grid_x = game->bomb.x / TILE_SIZE;
		bomb_grid_y = game->bomb.y / TILE_SIZE;
		if (game->map.map[bomb_grid_y][bomb_grid_x] == BOMB_ACTIVE)
		{
			if (!game->bomb.is_exploding)
			{
				mlx_put_image_to_window(game->mlx, game->win,
					game->texture.bg, game->bomb.x, game->bomb.y);
				mlx_put_image_to_window(game->mlx, game->win,
					game->bomb.sprites, game->bomb.x, game->bomb.y);
			}
		}
	}
}

int	render_map(t_game *game)
{
	int				j;
	static bool		first_render = true;

	if (first_render)
	{
		game->i = -1;
		while (++game->i < game->map.row)
		{
			j = -1;
			while (++j < game->map.col)
				render_map_texture(game, j);
		}
		first_render = false;
	}
	else
		render_bomb(game);
	if (game->enemy.alive)
		update_enemy(game);
	animate_coin(game);
	animate_player(game);
	return (0);
}

bool	has_required_elements(t_game *game)
{
	int		i;
	int		j;

	i = -1;
	while (++i < game->map.row)
	{
		j = -1;
		while (++j < game->map.col)
		{
			if (game->map.map[i][j] == 'P')
				game->map.player++;
			else if (game->map.map[i][j] == 'C')
				game->map.collectible++;
			else if (game->map.map[i][j] == 'E')
				game->map.exit++;
		}
	}
	if (game->map.player != 1)
		error("Error: The map should must have one character");
	if (game->map.collectible == 0)
		error("Error: The map should contain at least one collectible");
	if (game->map.exit != 1)
		error("Error: The map must have one exit");
	return (true);
}
