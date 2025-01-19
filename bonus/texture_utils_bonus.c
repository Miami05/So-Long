/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:33:35 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/18 14:56:49 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	load_bomb(t_game *game)
{
	const char	*explosion_path[4] = {
		"textures/bombs/bomb_1.xpm",
		"textures/bombs/bomb_2.xpm",
		"textures/bombs/bomb_3.xpm",
		"textures/bombs/bomb_4.xpm"
	};
	int			i;

	i = -1;
	game->bomb.sprites = mlx_xpm_file_to_image(game->mlx,
			"textures/bombs/bomb.xpm", &game->bomb.width, &game->bomb.height);
	if (!game->bomb.sprites)
		error("Error: Failed to load the bomb sprite");
	while (++i < 4)
	{
		game->bomb.explosion_sprites[i] = mlx_xpm_file_to_image(game->mlx,
				(char *)explosion_path[i], &game->bomb.width,
				&game->bomb.height);
		if (!game->bomb.explosion_sprites[i])
			error("Error: Failed to load the explosion sprites");
	}
}

void	load_player(t_game *game)
{
	const char	*sprites_path[4][3] = {
	{
		"textures/player/front_left.xpm",
		"textures/player/front.xpm",
		"textures/player/front_right.xpm"
	},
	{
		"textures/player/turn_left_left_foot.xpm",
		"textures/player/turn_left.xpm",
		"textures/player/turn_left_right_foot.xpm"
	},
	{
		"textures/player/turn_right_left_foot.xpm",
		"textures/player/turn_right.xpm",
		"textures/player/turn_right_right_foot.xpm"
	},
	{
		"textures/player/backwards_left_foot.xpm",
		"textures/player/backwards.xpm",
		"textures/player/backwards_right_foot.xpm"
	}
	};

	load_player_utils(game, sprites_path);
}

void	load_exit_door(t_game *game)
{
	game->texture.door = mlx_xpm_file_to_image(game->mlx,
			"textures/exit/door.xpm", &game->width, &game->height);
	game->texture.exit_door = mlx_xpm_file_to_image(game->mlx,
			"textures/exit/exit.xpm", &game->width, &game->height);
	if (!game->texture.door || !game->texture.exit_door)
		error("Error: Failed to load the door texture\n");
}

void	load_texture(t_game *game)
{
	game->texture.wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall/wall.xpm", &game->width, &game->height);
	game->texture.bg = mlx_xpm_file_to_image(game->mlx,
			"textures/background/background.xpm", &game->width, &game->height);
	if (!game->texture.wall || !game->texture.bg)
		error("Error: Failed to load the pictures");
	load_exit_door(game);
	load_player(game);
	load_enemy(game);
	load_bomb(game);
	load_sprites(game);
}
