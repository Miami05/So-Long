/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:46:47 by ledio             #+#    #+#             */
/*   Updated: 2024/12/24 20:41:08 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	while (++i < 4)
	{
		game->bomb.explosion_sprites[i] = mlx_xpm_file_to_image(game->mlx,
				(char *)explosion_path[i], &game->bomb.width,
				&game->bomb.height);
		if (!game->bomb.explosion_sprites[i])
			error("Error: Failed to load the explosion sprites");
	}
}

void	load_player_utils(t_game *game, const char *sprites_path[4][3])
{
	int			i;
	int			j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 3)
		{
			game->player.sprites[i][j] = mlx_xpm_file_to_image(game->mlx,
					(char *)sprites_path[i][j], &game->player.width,
					&game->player.height);
			if (!game->player.sprites[i][j])
				error("Error: Failed to load player sprites");
		}
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
	const char	*door_frames[2] = {
		"textures/exit/door.xpm",
		"textures/exit/exit.xpm"	
	};
	int			i;

	i = -1;
	while (++i < 2)
	{
		game->texture.exit_sprites[i] = mlx_xpm_file_to_image(game->mlx,
				(char *)door_frames[i], &game->width, &game->height);
		if (!game->texture.exit_sprites[i])
			error("Error: Failed load the door image");
	}
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
	load_bomb(game);
	load_sprites(game);
}
