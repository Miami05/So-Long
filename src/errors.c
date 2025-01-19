/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 01:06:52 by ledio             #+#    #+#             */
/*   Updated: 2025/01/18 13:44:01 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_map_valid_size(t_game *game)
{
	int		screen_width;
	int		screen_height;
	int		map_pixel_width;
	int		map_pixel_height;

	mlx_get_screen_size(game->mlx, &screen_width, &screen_height);
	map_pixel_width = game->map.col * TILE_SIZE;
	map_pixel_height = game->map.row * TILE_SIZE;
	if (map_pixel_width > screen_width || map_pixel_height > screen_height)
		return (false);
	return (true);
}

void	cleanup_player_sprites(t_game *game)
{
	int		i;
	int		j;

	if (!game || !game->player.sprites)
		return ;
	i = -1;
	while (++i < 4)
	{
		if (game->player.sprites[i])
		{
			j = -1;
			while (++j < 3)
			{
				if (game->player.sprites[i][j])
				{
					mlx_destroy_image(game->mlx, game->player.sprites[i][j]);
					game->player.sprites[i][j] = NULL;
				}
			}
			free(game->player.sprites[i]);
			game->player.sprites[i] = NULL;
		}
	}
	free(game->player.sprites);
	game->player.sprites = NULL;
}

void	exit_game(t_game *game)
{
	cleanup_player_sprites(game);
	free_map(game);
	free_bomb(game);
	free_box(game);
	free_textures(game);
	free_collectible_coins(game);
	if (game->win)
	{
		mlx_clear_window(game->mlx, game->win);
		mlx_destroy_window(game->mlx, game->win);
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
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
