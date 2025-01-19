/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:11:50 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/18 13:35:53 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_enemy_map(t_game *game)
{
	int		i;
	int		j;

	i = -1;
	while (++i < game->map.row)
	{
		j = -1;
		while (++j < game->map.col)
		{
			if (game->map.map[i][j] == 'X')
			{
				game->enemy.x = j;
				game->enemy.y = i;
				game->map.map[i][j] = '0';
			}
		}
	}
}

static void	load_enemy_sprite(t_game *game, int width,
	int height, const char *enemy[4][3])
{
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		game->enemy.sprites[i] = ft_calloc(3, sizeof(void *));
		if (!game->enemy.sprites[i])
		{
			free_enemy_sprite(game);
			error("Failed to allocate memory for the enemy sprites\n");
		}
		j = -1;
		while (++j < 3)
		{
			game->enemy.sprites[i][j] = mlx_xpm_file_to_image(game->mlx,
					(char *)enemy[i][j], &width, &height);
			if (!game->enemy.sprites[i][j])
			{
				free_enemy_sprite(game);
				error("Failed to load sprites\n");
			}
		}
	}
}

void	load_enemy_utils(t_game *game, const char *enemy[4][3])
{
	int		width;
	int		height;

	width = 0;
	height = 0;
	if (!game || !game->mlx)
		return ;
	game->enemy.sprites = ft_calloc(4, sizeof(void **));
	if (!game->enemy.sprites)
		error("Failed to allocate memory for the enemy sprite\n");
	load_enemy_sprite(game, width, height, enemy);
}

void	load_enemy(t_game *game)
{
	const char	*enemy[4][3] = {
	{
		"textures/enemy/front.xpm",
		"textures/enemy/front_left.xpm",
		"textures/enemy/front_right.xpm"
	},
	{
		"textures/enemy/turn_left_foot.xpm",
		"textures/enemy/turn_left_right_foot.xpm",
		"textures/enemy/turn_left.xpm"
	},
	{
		"textures/enemy/turn_right_foot.xpm",
		"textures/enemy/turn_right_left_foot.xpm",
		"textures/enemy/turn_right.xpm"
	},
	{
		"textures/enemy/backwards_left.xpm",
		"textures/enemy/backwards_right.xpm",
		"textures/enemy/backwards.xpm"
	}
	};

	load_enemy_utils(game, enemy);
}
