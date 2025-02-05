/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:23:57 by ledio             #+#    #+#             */
/*   Updated: 2025/02/05 21:58:08 by ldurmish         ###   ########.fr       */
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
				&& game->map.map[i][j] != 'E')
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

void	init_vars(t_game *game)
{
	int			i;
	int			j;

	i = -1;
	while (++i < game->map.row)
	{
		j = -1;
		while (++j < ft_strlen(game->map.map[i]))
		{
			if (game->map.map[i][j] == 'C')
				game->player.max_coins++;
		}
	}
}
