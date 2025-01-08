/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:46:20 by ledio             #+#    #+#             */
/*   Updated: 2024/12/20 19:05:53 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(char **map_copy, int row, int col, t_game *game)
{
	if (row < 0 || col < 0 || row >= game->map.row || col >= game->map.col
		|| map_copy[row][col] == '1' || map_copy[row][col] == 'F')
		return ;
	map_copy[row][col] = 'F';
	flood_fill(map_copy, row + 1, col, game);
	flood_fill(map_copy, row - 1, col, game);
	flood_fill(map_copy, row, col + 1, game);
	flood_fill(map_copy, row, col - 1, game);
}

static void	find_player(t_game *game, int *row, int *col)
{
	int			i;
	int			j;

	i = 0;
	while (i < game->map.row)
	{
		j = 0;
		while (j < game->map.col)
		{
			if (game->map.map[i][j] == 'P')
			{
				*row = i;
				*col = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

static char	**get_map_copy(t_game *game)
{
	char		**map_copy;
	int			i;

	map_copy = (char **)malloc(sizeof(char *) * game->map.row);
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < game->map.row)
	{
		map_copy[i] = ft_strdup(game->map.map[i]);
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	return (map_copy);
}

static bool	check_reachable(char **map_copy, t_game *game)
{
	int			i;
	int			j;

	i = 0;
	while (i < game->map.row)
	{
		j = 0;
		while (j < game->map.col)
		{
			if ((map_copy[i][j] == 'C' || map_copy[i][j] == 'E')
				&& map_copy[i][j] != 'F')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	is_path_valid(t_game *game)
{
	char		**map_copy;
	int			row;
	int			col;
	bool		is_valid;

	map_copy = get_map_copy(game);
	if (!map_copy)
		error("Error: Memory allocation failed\n");
	find_player(game, &row, &col);
	flood_fill(map_copy, row, col, game);
	is_valid = check_reachable(map_copy, game);
	free_map_copy(map_copy, game);
	if (!is_valid)
		error("Error: Not all elements are reachable\n");
	return (true);
}
