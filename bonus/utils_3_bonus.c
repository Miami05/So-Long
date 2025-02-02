/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:23:36 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/23 20:56:04 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	check_explosion_utils(t_game *game, int grid_x, int grid_y)
{
	if (grid_x == game->player.x / TILE_SIZE
		&& grid_y == game->player.y / TILE_SIZE)
	{
		ft_printf("You lost\n");
		exit_game(game);
	}
	if (game->map.map[grid_y][grid_x] == 'B')
	{
		game->map.map[grid_y][grid_x] = '0';
		mlx_put_image_to_window(game->mlx, game->win,
			game->texture.bg, grid_x * TILE_SIZE, grid_y * TILE_SIZE);
	}
	else if (game->map.map[grid_y][grid_x] == '3')
	{
		animate_coin(game);
		game->player.collected_coins++;
		game->map.collectible--;
		game->map.map[grid_y][grid_x] = '0';
		mlx_put_image_to_window(game->mlx, game->win,
			game->texture.bg, grid_x * TILE_SIZE, grid_y * TILE_SIZE);
	}
}

void	check_explosion(t_game *game, int pos_x, int pos_y)
{
	int		grid_x;
	int		grid_y;

	if (!game || !game->mlx || !game->win)
		return ;
	grid_x = pos_x / TILE_SIZE;
	grid_y = pos_y / TILE_SIZE;
	if (grid_x < 0 || grid_x >= game->map.col
		|| grid_y < 0 || grid_y >= game->map.row)
		return ;
	if (game->enemy.alive)
	{
		if (grid_x == game->enemy.x && grid_y == game->enemy.y)
		{
			game->enemy.alive = 0;
			mlx_put_image_to_window(game->mlx, game->win,
				game->texture.bg, game->enemy.x * TILE_SIZE,
				game->enemy.y * TILE_SIZE);
			ft_printf("Enemy defeated!\n");
		}
	}
	check_explosion_utils(game, grid_x, grid_y);
}

static void	render_explosion_direction(t_game *game, int dir_x, int dir_y)
{
	int		pos_x;
	int		pos_y;
	int		i;
	int		radius;

	radius = game->player.bomb_power;
	i = 1;
	pos_x = game->bomb.x / TILE_SIZE;
	pos_y = game->bomb.y / TILE_SIZE;
	while (i <= radius)
	{
		pos_x += dir_x;
		pos_y += dir_y;
		if (pos_x < 0 || pos_x >= game->map.col
			|| pos_y < 0 || pos_y >= game->map.row
			|| game->map.map[pos_y][pos_x] == '1'
			|| game->map.map[pos_y][pos_x] == 'E')
			break ;
		mlx_put_image_to_window(game->mlx, game->win,
			game->bomb.explosion_sprites[game->bomb.explosion_frame],
			pos_x * TILE_SIZE, pos_y * TILE_SIZE);
		check_explosion(game, pos_x * TILE_SIZE, pos_y * TILE_SIZE);
		i++;
	}
}

void	render_explosion(t_game *game)
{
	int		bomb_x;
	int		bomb_y;

	bomb_x = game->bomb.x / TILE_SIZE;
	bomb_y = game->bomb.y / TILE_SIZE;
	if (game->map.map[bomb_y][bomb_x] != 'E')
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->bomb.explosion_sprites[game->bomb.explosion_frame],
			game->bomb.x, game->bomb.y);
		check_explosion(game, game->bomb.x, game->bomb.y);
	}
	render_explosion_direction(game, 1, 0);
	render_explosion_direction(game, -1, 0);
	render_explosion_direction(game, 0, 1);
	render_explosion_direction(game, 0, -1);
}

void	free_enemy_sprite(t_game *game)
{
	int		i;
	int		j;

	if (!game->enemy.sprites)
		return ;
	i = -1;
	while (++i < 4)
	{
		if (game->enemy.sprites[i])
		{
			j = -1;
			while (++j < 3)
			{
				if (game->enemy.sprites[i][j])
				{
					mlx_destroy_image(game->mlx, game->enemy.sprites[i][j]);
					game->enemy.sprites[i][j] = NULL;
				}
			}
			free(game->enemy.sprites[i]);
			game->enemy.sprites[i] = NULL;
		}
	}
	free(game->enemy.sprites);
	game->enemy.sprites = NULL;
}
