/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 23:46:46 by ledio             #+#    #+#             */
/*   Updated: 2025/01/17 21:05:23 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_explosion(t_game *game, int pos_x, int pos_y)
{
	int		grid_x;
	int		grid_y;

	if (!game || !game->mlx || !game->win)
		return ;
	grid_x = pos_x / TILE_SIZE;
	grid_y = pos_y / TILE_SIZE;
	if (grid_x < 0 || grid_x >= game->map.col ||
		grid_y < 0 || grid_y >= game->map.row)
		return ;
	if (grid_x == game->player.x / TILE_SIZE
		&& grid_y == game->player.y / TILE_SIZE)
	{
		error("You lost\n");
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
	int bomb_x = game->bomb.x / TILE_SIZE;
	int bomb_y = game->bomb.y / TILE_SIZE;

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

void	setup_game_tools(t_game *game)
{
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, (void *)exit_game, game);
}

void	animate_coin(t_game *game)
{
	static int		frame_count = 0;
	int				j;

	frame_count++;
	if (frame_count >= game->coins.anim_speed)
	{
		game->coins.current_frame = (game->coins.current_frame + 1) % 9;
		frame_count = 0;
	}
	game->i = -1;
	while (++game->i < game->map.row)
	{
		j = -1;
		while (++j < game->map.col)
		{
			if (game->map.map[game->i][j] == 'C')
			{
				mlx_put_image_to_window(game->mlx, game->win,
					game->texture.bg, j * TILE_SIZE, game->i * TILE_SIZE);
				mlx_put_image_to_window(game->mlx, game->win,
					game->coins.sprites[game->coins.current_frame],
					j * TILE_SIZE, game->i * TILE_SIZE);
			}
		}
	}
}
