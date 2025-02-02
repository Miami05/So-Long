/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:10:05 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/23 20:50:29 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_bomb(t_game *game)
{
	int		i;

	if (game->bomb.sprites)
	{
		mlx_destroy_image(game->mlx, game->bomb.sprites);
		game->bomb.sprites = NULL;
	}
	i = 0;
	while (i < 4)
	{
		if (game->bomb.explosion_sprites[i])
		{
			mlx_destroy_image(game->mlx, game->bomb.explosion_sprites[i]);
			game->bomb.explosion_sprites[i] = NULL;
		}
		i++;
	}
}

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

void	free_box(t_game *game)
{
	if (game && game->mlx && game->box.sprites)
	{
		mlx_destroy_image(game->mlx, game->box.sprites);
		game->box.sprites = NULL;
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
