/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 23:46:46 by ledio             #+#    #+#             */
/*   Updated: 2024/12/24 17:45:02 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	animate_coin(t_game *game)
{
	static int		frame_count = 0;
	int				j;

	frame_count++;
	if (frame_count >= game->coins.anim_speed)
	{
		game->coins.current_frame = (game->coins.current_frame + 1) % 9;
		frame_count = 0;
	}
	game->i = -1;
	while (++game->i < game->map.row)
	{
		j = -1;
		while (++j < game->map.col)
		{
			if (game->map.map[game->i][j] == 'C')
			{
				mlx_put_image_to_window(game->mlx, game->win,
					game->texture.bg, j * TILE_SIZE, game->i * TILE_SIZE);
				mlx_put_image_to_window(game->mlx, game->win,
					game->coins.sprites[game->coins.current_frame],
					j * TILE_SIZE, game->i * TILE_SIZE);
			}
		}
	}
}
