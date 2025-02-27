/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:53:27 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/20 15:23:13 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
