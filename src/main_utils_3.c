/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 00:51:08 by ledio             #+#    #+#             */
/*   Updated: 2025/01/20 13:15:42 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_valid_character(char c)
{
	return (c == '1' || c == 'E'
		|| c == 'C' || c == '0' || c == 'P');
}

bool	valid_map_character(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->map.row)
	{
		j = 0;
		while (j < game->map.col)
		{
			if (!is_valid_character(game->map.map[i][j]))
			{
				ft_printf("Error: Invalid character\n");
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

static void	render_map_texture(t_game *game, int j)
{
	mlx_put_image_to_window(game->mlx, game->win, game->texture.bg,
		j * TILE_SIZE, game->i * TILE_SIZE);
	if (game->map.map[game->i][j] == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->texture.wall, j * TILE_SIZE, game->i * TILE_SIZE);
	else if (game->map.map[game->i][j] == 'E')
	{
		if (game->player.collected_coins >= game->player.coins_needed)
			mlx_put_image_to_window(game->mlx, game->win,
				game->texture.exit_door, j * TILE_SIZE, game->i * TILE_SIZE);
		mlx_put_image_to_window(game->mlx, game->win,
			game->texture.door, j * TILE_SIZE, game->i * TILE_SIZE);
	}
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
	animate_coin(game);
	animate_player(game);
	return (0);
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
