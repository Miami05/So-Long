/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:59:39 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/18 13:56:23 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	setup_game_tools(t_game *game)
{
	init_enemy(game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, (void *)exit_game, game);
}

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
