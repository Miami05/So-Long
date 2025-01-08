/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:37:38 by ledio             #+#    #+#             */
/*   Updated: 2024/12/24 17:09:58 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player(t_game *game)
{
	int			i;
	int			j;

	i = -1;
	while (++i < game->map.row)
	{
		j = -1;
		while (++j < game->map.col)
		{
			if (game->map.map[i][j] == 'P')
			{
				game->player.x = j * TILE_SIZE;
				game->player.y = i * TILE_SIZE;
				game->map.map[i][j] = '0';
			}
		}
	}
}

bool	is_valid_move(t_game *game, int grid_x, int grid_y)
{
	if (grid_x < 0 || grid_y < 0 || grid_x >= game->map.col
		|| grid_y >= game->map.row)
		return (false);
	if (game->map.map[grid_y][grid_x] == '1')
		return (false);
	if (game->map.map[grid_y][grid_x] == 'B'
		|| game->map.map[grid_y][grid_x] == '3')
		return (false);
	if (game->map.map[grid_y][grid_x] == 'E'
			&& game->map.collectible > 0)
		return (false);
	return (true);
}

void	move_player(t_game *game, int new_grid_x, int new_grid_y)
{
	game->player.x = new_grid_x * TILE_SIZE;
	game->player.y = new_grid_y * TILE_SIZE;
	game->player.moves++;
	if (game->map.map[new_grid_y][new_grid_x] == 'C')
	{
		game->map.map[new_grid_y][new_grid_x] = '0';
		game->map.collectible--;
		game->player.collected_coins++;
		if (game->player.collected_coins % 3 == 0
			&& game->player.explosion_power < 3)
			game->player.explosion_power++;
	}
	ft_printf("Moves: %d | Coins: %d/%d | Bomb Power: %d\n",
		game->player.moves, game->player.collected_coins,
		game->player.max_coins, game->player.explosion_power);
	if (game->map.map[new_grid_y][new_grid_x] == 'E'
		&& game->map.collectible == 0)
	{
		ft_printf("Congratulations! You won in %d moves!.\n",
			game->player.moves);
		exit_game(game);
	}
}

void	animate_player(t_game *game)
{
	void			*current_sprite;
	static int		prev_x = -1;
	static int		prev_y = -1;

	if (prev_x != game->player.x || prev_y != game->player.y)
		mlx_put_image_to_window(game->mlx, game->win, game->texture.bg,
			prev_x, prev_y);
	if (game->player.is_moving)
	{
		game->player.frame_count++;
		if (game->player.frame_count >= 15)
		{
			game->player.current_frame = (game->player.current_frame + 1) % 3;
			game->player.frame_count = 0;
		}
	}
	else
		game->player.current_frame = 1;
	current_sprite = game->player.sprites
	[game->player.direction][game->player.current_frame];
	mlx_put_image_to_window(game->mlx, game->win, current_sprite,
		game->player.x, game->player.y);
	prev_x = game->player.x;
	prev_y = game->player.y;
}
