/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:58:04 by ledio             #+#    #+#             */
/*   Updated: 2025/01/17 21:07:05 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_bomb(t_game *game)
{
	game->player.bomb_power = 2;
	game->bomb.explosion_duration = 20;
	game->bomb.explosion_radius = game->player.bomb_power;
	game->bomb.is_exploding = false;
}

void	load_collectible(t_game *game)
{
	const char		*coins_path[9] = {
		"textures/coins/coins.xpm",
		"textures/coins/coins_1.xpm",
		"textures/coins/coins_2.xpm",
		"textures/coins/coins_3.xpm",
		"textures/coins/coins_4.xpm",
		"textures/coins/coins_5.xpm",
		"textures/coins/coins_6.xpm",
		"textures/coins/coins_7.xpm",
		"textures/coins/coins_8.xpm"
	};
	int				i;

	i = -1;
	while (++i < 9)
	{
		game->coins.sprites[i] = mlx_xpm_file_to_image(game->mlx,
				(char *)coins_path[i], &game->coins.width,
				&game->coins.height);
		if (!game->coins.sprites[i])
			error("Error: Failed to load the coins sprites");
	}
}

void	load_box(t_game *game)
{
	game->box.sprites = mlx_xpm_file_to_image(game->mlx,
			"textures/box/box.xpm", &game->box.width,
			&game->box.height);
	if (!game->box.sprites)
		error("Error: Failed loading box sprites");
}

void	load_sprites(t_game *game)
{
	load_box(game);
	load_collectible(game);
}
