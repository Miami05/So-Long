/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:31:40 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/16 13:52:42 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
				&& game->map.map[i][j] != '3' && game->map.map[i][j] != 'X')
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

	if (!game || !game->map.map || !game->map.map[0])
		return (false);
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
	if (!valid_map_character(game))
		error("Error: There are invalid characters\n");
	if (!is_path_valid(game))
		error("Error: There is no valid path in the map\n");
	return (true);
}

void	init_vars(t_game *game)
{
	int			i;
	int			j;

	init_bomb(game);
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
