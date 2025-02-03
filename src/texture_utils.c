/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:46:47 by ledio             #+#    #+#             */
/*   Updated: 2025/02/03 14:58:29 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			error("Error: Failed to load the coins sprites", game);
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
		error("Error: Failed to load the door texture\n", game);
}

void	load_texture(t_game *game)
{
	game->texture.wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall/wall.xpm", &game->width, &game->height);
	game->texture.bg = mlx_xpm_file_to_image(game->mlx,
			"textures/background/background.xpm", &game->width, &game->height);
	if (!game->texture.wall || !game->texture.bg)
		error("Error: Failed to load the pictures", game);
	load_exit_door(game);
	load_player(game);
	load_collectible(game);
}
