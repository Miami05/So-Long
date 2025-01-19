/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:57:19 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/19 19:57:48 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	flood_fill(char **map_copy, int row, int col, t_game *game)
{
	if (row < 0 || col < 0 || row >= game->map.row || col >= game->map.col
		|| map_copy[row][col] == '1' || map_copy[row][col] == 'F')
		return ;
	map_copy[row][col] = 'F';
	if (game->map.map[row][col] == 'C'
		|| game->map.map[row][col] == '3')
		game->valid.coins++;
	if (game->map.map[row][col] == 'E')
	{
		game->valid.exit = 1;
		return ;
	}
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

static bool	check_reachable(t_game *game)
{
	if (game->valid.coins < game->player.max_coins)
	{
		ft_printf("Failed: Coins reachable: %d, Total coins needed: %d\n",
			game->valid.coins, game->player.max_coins);
		return (false);
	}
	if (!game->valid.exit)
	{
		ft_printf("Failed: Exit not reachable\n");
		return (false);
	}
	return (true);
}

bool	is_path_valid(t_game *game)
{
	char		**map_copy;
	int			row;
	int			col;
	bool		is_valid;

	game->valid.coins = 0;
	game->valid.exit = 0;
	map_copy = get_map_copy(game);
	if (!map_copy)
		error("Error: Memory allocation failed\n");
	find_player(game, &row, &col);
	flood_fill(map_copy, row, col, game);
	is_valid = check_reachable(game);
	free_map_copy(map_copy, game);
	if (!is_valid)
		error("Error: Not all elements are reachable\n");
	return (true);
}
