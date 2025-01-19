/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_player_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:38:42 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/18 13:40:46 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
				game->player.initial_x = game->player.x;
				game->player.initial_y = game->player.y;
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
	if (game->map.map[grid_y][grid_x] == BOMB_ACTIVE)
		return (false);
	return (true);
}

static void	move_player_utils(t_game *game, int new_grid_x, int new_grid_y)
{
	if (game->map.map[new_grid_y][new_grid_x] == 'C')
	{
		game->map.map[new_grid_y][new_grid_x] = '0';
		game->map.collectible--;
		game->player.collected_coins++;
		if (game->player.collected_coins % 3 == 0
			&& game->player.explosion_power < 3)
			game->player.explosion_power++;
		ft_printf("Coins collected! Remaining: %d\n", game->map.collectible);
	}
	if (game->enemy.alive && new_grid_x == game->player.x
		&& new_grid_y == game->player.y)
	{
		ft_printf("Game Over! Caught by the enemy!\n");
		exit_game(game);
	}
}

void	move_player(t_game *game, int new_grid_x, int new_grid_y)
{
	int			prev_x;
	int			prev_y;

	prev_x = game->player.x;
	prev_y = game->player.y;
	game->player.x = new_grid_x * TILE_SIZE;
	game->player.y = new_grid_y * TILE_SIZE;
	game->player.moves++;
	move_player_utils(game, new_grid_x, new_grid_y);
	if (game->map.map[new_grid_y][new_grid_x] == 'E')
	{
		if (game->map.collectible == 0 && !game->enemy.alive)
		{
			ft_printf("Congratulations! You won in %d moves!\n",
				game->player.moves);
			exit_game(game);
		}
		else
		{
			game->player.x = prev_x;
			game->player.y = prev_y;
		}
	}
}
