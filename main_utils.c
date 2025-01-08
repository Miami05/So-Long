/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:23:57 by ledio             #+#    #+#             */
/*   Updated: 2024/12/24 17:50:42 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	has_valid_characters(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->map.row)
	{
		j = 0;
		while (j < ft_strlen(game->map.map[i]))
		{
			if (game->map.map[i][j] != '1' && game->map.map[i][j] != '0'
				&& game->map.map[i][j] != 'C' && game->map.map[i][j] != 'P'
				&& game->map.map[i][j] != 'E' && game->map.map[i][j] != 'B'
				&& game->map.map[i][j] != '3')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	is_enclosed_by_walls(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->map.col)
	{
		if (game->map.map[0][i] != '1'
			|| game->map.map[game->map.row - 1][i] != '1')
			return (false);
		i++;
	}
	i = 0;
	while (i < game->map.row)
	{
		if (game->map.map[i][0] != '1'
			|| game->map.map[i][game->map.col - 1] != '1')
			return (false);
		i++;
	}
	return (true);
}

bool	is_rectangular(t_game *game)
{
	int		len;
	int		i;

	len = ft_strlen(game->map.map[0]);
	i = 1;
	while (i < game->map.row)
	{
		if (ft_strlen(game->map.map[i]) != len)
			return (false);
		i++;
	}
	return (true);
}

bool	validate_map(t_game *game)
{
	if (!is_rectangular(game))
		error("Error: The map should be rectangular\n");
	if (!is_enclosed_by_walls(game))
		error("Error: The map should be enclosed by walls\n");
	if (!has_valid_characters(game))
		error("Error: Invalid characters found in the map\n");
	if (!has_required_elements(game))
		error("Error: Invalid number of players, exit or collectibles\n");
	if (!is_path_valid(game))
		error("Error: There is no valid path in the map\n");
	return (true);
}

void	init_vars(t_game *game)
{
	int			i;
	int			j;

	ft_memset(game, 0, sizeof(t_game));
	game->player.direction = 0;
	game->width = TILE_SIZE;
	game->height = TILE_SIZE;
	game->player.is_moving = false;
	game->player.current_frame = 1;
	game->player.explosion_power = 1;
	game->player.bomb_power = 1;
	game->coins.anim_speed = 300;
	game->player.coins_needed = 3;
	i = -1;
	while (++i < game->map.row)
	{
		j = -1;
		while (++j < game->map.col)
		{
			if (game->map.map[i][j] == 'C'
			|| game->map.map[i][j] == '3')
				game->player.max_coins++;
		}
	}
}
