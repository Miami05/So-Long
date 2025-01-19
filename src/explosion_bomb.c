/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explosion_bomb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 21:45:35 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/17 21:24:14 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_valid_character(char c)
{
	return (c == '1' || c == 'E'
		|| c == 'C' || c == '0' || c == 'P');
}

bool	valid_map_character(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->map.row)
	{
		j = 0;
		while (j < game->map.col)
		{
			if (!is_valid_character(game->map.map[i][j]))
			{
				ft_printf("Error: Invalid character\n");
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

void	clear_explosion_direction(t_game *game, int dir_x, int dir_y)
{
	int		i;
	int		bomb_x;
	int		bomb_y;
	int		pos_x;
	int		pos_y;

	i = 1;
	bomb_x = game->bomb.x / TILE_SIZE;
	bomb_y = game->bomb.y / TILE_SIZE;
	pos_x = bomb_x;
	pos_y = bomb_y;
	while (i <= game->player.bomb_power)
	{
		pos_x += dir_x;
		pos_y += dir_y;
		if (pos_x < 0 || pos_x >= game->map.col
			|| pos_y < 0 || pos_y >= game->map.row
			|| game->map.map[pos_y][pos_x] == '1'
			|| game->map.map[pos_y][pos_x] == 'E')
			break ;
		mlx_put_image_to_window(game->mlx, game->win,
			game->texture.bg, pos_x * TILE_SIZE, pos_y * TILE_SIZE);
		i++;
	}
}

void	clear_explosion_area(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->texture.bg, game->bomb.x, game->bomb.y);
	clear_explosion_direction(game, 1, 0);
	clear_explosion_direction(game, -1, 0);
	clear_explosion_direction(game, 0, 1);
	clear_explosion_direction(game, 0, -1);
}
