/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:57:46 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/20 14:21:01 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_collectible_coins(t_game *game)
{
	int		i;

	if (game && game->mlx)
	{
		i = 0;
		while (i < 9)
		{
			if (game->coins.sprites[i])
			{
				mlx_destroy_image(game->mlx, game->coins.sprites[i]);
				game->coins.sprites[i] = NULL;
			}
			i++;
		}
	}
}

void	free_textures(t_game *game)
{
	if (game && game->mlx)
	{
		if (game->texture.bg)
		{
			mlx_destroy_image(game->mlx, game->texture.bg);
			game->texture.bg = NULL;
		}
		if (game->texture.wall)
		{
			mlx_destroy_image(game->mlx, game->texture.wall);
			game->texture.wall = NULL;
		}
		if (game->texture.door)
		{
			mlx_destroy_image(game->mlx, game->texture.door);
			game->texture.door = NULL;
		}
		if (game->texture.exit_door)
		{
			mlx_destroy_image(game->mlx, game->texture.exit_door);
			game->texture.exit_door = NULL;
		}
	}
}

void	free_map(t_game *game)
{
	int		i;

	if (game->map.map)
	{
		i = 0;
		while (i < game->map.row)
		{
			if (game->map.map[i])
			{
				free(game->map.map[i]);
				game->map.map[i] = NULL;
			}
			i++;
		}
		free(game->map.map);
		game->map.map = NULL;
	}
}
