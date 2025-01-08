/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 00:51:08 by ledio             #+#    #+#             */
/*   Updated: 2024/12/24 18:09:15 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_map_utils(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	i = game->player.prev_y / TILE_SIZE;
	j = game->player.prev_x / TILE_SIZE;
	mlx_put_image_to_window(game->mlx, game->win, game->texture.bg,
		game->player.prev_x, game->player.prev_y);
	if (game->map.map[i][j] == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->texture.wall, game->player.prev_x, game->player.prev_y);
}

static void	render_map_texture(t_game *game, int j)
{
	mlx_put_image_to_window(game->mlx, game->win, game->texture.bg,
		j * TILE_SIZE, game->i * TILE_SIZE);
	if (game->map.map[game->i][j] == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->texture.wall, j * TILE_SIZE, game->i * TILE_SIZE);
	else if (game->map.map[game->i][j] == 'B'
		|| game->map.map[game->i][j] == '3')
		mlx_put_image_to_window(game->mlx, game->win,
			game->box.sprites, j * TILE_SIZE, game-> i * TILE_SIZE);
}

int	render_map(t_game *game)
{
	int				j;
	static bool		first_render = true;

	if (first_render)
	{
		game->i = -1;
		while (++game->i < game->map.row)
		{
			j = -1;
			while (++j < game->map.col)
				render_map_texture(game, j);
		}
		first_render = false;
	}
	else if (game->player.prev_x != game->player.x
		|| game->player.prev_y != game->player.y)
		render_map_utils(game);
	update_bomb_state(game);
	if (game->bomb.active && game->bomb.is_exploding)
		render_explosion(game);
	animate_coin(game);
	animate_player(game);
	return (0);
}

void	setup_game_tools(t_game *game)
{
	mlx_loop_hook(game->mlx, render_map, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, (void *)exit_game, game);
}

bool	has_required_elements(t_game *game)
{
	int		i;
	int		j;

	i = -1;
	while (++i < game->map.row)
	{
		j = -1;
		while (++j < game->map.col)
		{
			if (game->map.map[i][j] == 'P')
				game->map.player++;
			else if (game->map.map[i][j] == 'C')
				game->map.collectible++;
			else if (game->map.map[i][j] == 'E')
				game->map.exit++;
		}
	}
	if (game->map.player != 1)
		error("Error: The map should must have one character");
	if (game->map.collectible == 0)
		error("Error: The map should contain at least one collectible");
	if (game->map.exit != 1)
		error("Error: The map must have one exit");
	return (true);
}
