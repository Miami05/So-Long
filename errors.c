/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 01:06:52 by ledio             #+#    #+#             */
/*   Updated: 2024/12/22 02:12:09 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_game(t_game *game)
{
	mlx_destroy_display(game->mlx);
	mlx_destroy_window(game->mlx, game->win);
	free(game->mlx);
	exit(EXIT_FAILURE);
}

void	free_map_copy(char **map_copy, t_game *game)
{
	int			i;

	i = 0;
	while (i < game->map.row)
		free(map_copy[i++]);
	free(map_copy);
}

int	error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
