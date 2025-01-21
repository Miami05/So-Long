/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:56:32 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/20 15:12:08 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	render_map_utils(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	i = game->player.prev_y / TILE_SIZE;
	j = game->player.prev_x / TILE_SIZE;
	if (game->map.map[i][j] != '1')
		mlx_put_image_to_window(game->mlx, game->win, game->texture.bg,
			game->player.prev_x, game->player.prev_y);
	else
		mlx_put_image_to_window(game->mlx, game->win,
			game->texture.wall, game->player.prev_x, game->player.prev_y);
}

void	render_bomb(t_game *game)
{
	int		bomb_grid_x;
	int		bomb_grid_y;

	if (game->player.prev_x != game->player.x
		|| game->player.prev_y != game->player.y)
	{
		render_map_utils(game);
	}
	if (game->bomb.active)
	{
		bomb_grid_x = game->bomb.x / TILE_SIZE;
		bomb_grid_y = game->bomb.y / TILE_SIZE;
		if (game->map.map[bomb_grid_y][bomb_grid_x] == BOMB_ACTIVE)
		{
			if (!game->bomb.is_exploding)
			{
				mlx_put_image_to_window(game->mlx, game->win,
					game->texture.bg, game->bomb.x, game->bomb.y);
				mlx_put_image_to_window(game->mlx, game->win,
					game->bomb.sprites, game->bomb.x, game->bomb.y);
			}
		}
	}
}

void	has_required_elemets_utils(t_game *game)
{
	if (game->map.player != 1)
	{
		ft_printf("Error: The map should must have one character\n");
		exit_game(game);
	}
	if (game->map.collectible == 0)
	{
		ft_printf("Error: The map should contain at least one collectible\n");
		exit_game(game);
	}
	if (game->map.exit != 1)
	{
		ft_printf("Error: The map must have one exit\n");
		exit_game(game);
	}
	if (game->map.enemy != 1)
	{
		ft_printf("Error: The map mus have one enemy");
		exit_game(game);
	}
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
			else if (game->map.map[i][j] == 'X')
				game->map.enemy++;
		}
	}
	has_required_elemets_utils(game);
	return (true);
}
