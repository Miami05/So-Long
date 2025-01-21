/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:45:43 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/20 15:13:32 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	has_required_elemets_utils(t_game *game)
{
	if (game->map.player != 1)
	{
		ft_printf("Error: The map should must have one character\n");
		exit_game(game);
	}
	if (game->map.collectible == 0)
	{
		ft_printf("Error: The map should contain at least one collectible\n");
		exit_game(game);
	}
	if (game->map.exit != 1)
	{
		ft_printf("Error: The map must have one exit\n");
		exit_game(game);
	}
}

bool	has_required_elements(t_game *game)
{
	int		i;
	int		j;

	i = -1;
	while (++i < game->map.row)
	{
		j = -1;
		while (++j < game->map.col)
		{
			if (game->map.map[i][j] == 'P')
				game->map.player++;
			else if (game->map.map[i][j] == 'C')
				game->map.collectible++;
			else if (game->map.map[i][j] == 'E')
				game->map.exit++;
		}
	}
	has_required_elemets_utils(game);
	return (true);
}

void	validate_maps_utils(t_game *game)
{
	if (!valid_map_character(game))
	{
		ft_printf("Error: There are invalid characters\n");
		exit_game(game);
	}
	if (!is_path_valid(game))
	{
		ft_printf("Error: There is no valid path in the map\n");
		exit_game(game);
	}
}

bool	validate_map(t_game *game)
{
	if (!is_rectangular(game))
	{
		ft_printf("Error: The map should be rectangular\n");
		exit_game(game);
	}
	if (!is_enclosed_by_walls(game))
	{
		ft_printf("Error: The map should be enclosed by walls\n");
		exit_game(game);
	}
	if (!has_valid_characters(game))
	{
		ft_printf("Error: Invalid characters found in the map\n");
		exit_game(game);
	}
	if (!has_required_elements(game))
	{
		ft_printf("Error: Invalid number of players, exit or collectibles\n");
		exit_game(game);
	}
	validate_maps_utils(game);
	return (true);
}
