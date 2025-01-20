/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:06:44 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/20 12:59:19 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	calculate_distance(int x1, int y1, int x2, int y2)
{
	return (abs(x1 - x2) + abs(y1 - y2));
}

void	init_enemy(t_game *game)
{
	const int		min_safe_distance = 5;
	int				player_tile_x;
	int				player_tile_y;

	player_tile_x = game->player.x / TILE_SIZE;
	player_tile_y = game->player.y / TILE_SIZE;
	game->enemy.alive = 1;
	game->enemy.width = 32;
	game->enemy.height = 32;
	game->enemy.current_frame = 0;
	game->enemy.direction = 0;
	game->enemy.x = rand() % (game->map.col - 2) + 1;
	game->enemy.y = rand() % (game->map.row - 2) + 1;
	while (game->map.map[game->enemy.y][game->enemy.x] != '0'
		|| calculate_distance(game->enemy.x, game->enemy.y,
			player_tile_x, player_tile_y) < min_safe_distance)
	{
		game->enemy.x = rand() % (game->map.col - 2) + 1;
		game->enemy.y = rand() % (game->map.row - 2) + 1;
	}
}
