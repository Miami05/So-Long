/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:57:46 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/18 13:42:43 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		{
			free(game->map.map[i]);
			i++;
		}
		free(game->map.map);
		game->map.map = NULL;
	}
}
