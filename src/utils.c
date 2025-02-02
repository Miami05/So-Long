/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:01:04 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/31 16:56:24 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_player_sprite(t_game *game, const char *sprites_path[4][3],
	int width, int height)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		game->player.sprites[i] = ft_calloc(3, sizeof(void *));
		if (!game->player.sprites[i])
		{
			cleanup_player_sprites(game);
			error("Failed to allocate memory for player sprite frames");
		}
		j = -1;
		while (++j < 3)
		{
			game->player.sprites[i][j] = mlx_xpm_file_to_image(game->mlx,
					(char *)sprites_path[i][j], &width, &height);
			if (!game->player.sprites[i][j])
			{
				cleanup_player_sprites(game);
				error("Failed to load player sprite");
			}
		}
	}
}

void	load_player_utils(t_game *game, const char *sprites_path[4][3])
{
	int		width;
	int		height;

	width = 0;
	height = 0;
	if (!game || !game->mlx)
		return ;
	game->player.sprites = calloc(4, sizeof(void **));
	if (!game->player.sprites)
		error("Failed to allocate memory for player sprites");
	load_player_sprite(game, sprites_path, width, height);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_A || keycode == KEY_D || keycode == KEY_S
		|| keycode == KEY_W || keycode == KEY_UP || keycode == KEY_DOWN
		|| keycode == KEY_RIGHT || keycode == KEY_LEFT)
	{
		game->player.is_moving = false;
		game->player.current_frame = 1;
	}
	return (0);
}
