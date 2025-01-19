/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_player_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:04:26 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/18 15:02:16 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

void	update_enemy(t_game *game)
{
	if (game->enemy.alive)
		render_enemy(game);
}

void	animate_player_utils(t_game *game, int prev_x, int prev_y)
{
	if (prev_x >= 0 && prev_y >= 0 && game->texture.bg)
		mlx_put_image_to_window(game->mlx, game->win, game->texture.bg, prev_x,
			prev_y);
	if (game->player.is_moving)
	{
		game->player.frame_count++;
		if (game->player.frame_count >= 15)
		{
			game->player.current_frame = (game->player.current_frame + 1) % 3;
			game->player.frame_count = 0;
		}
	}
	else
		game->player.current_frame = 1;
}

void	animate_player(t_game *game)
{
	void		*current_sprite;
	static int	prev_x = -1;
	static int	prev_y = -1;

	current_sprite = NULL;
	if (!game || !game->mlx || !game->win || !game->player.sprites)
		return ;
	if (prev_x != game->player.x || prev_y != game->player.y
		|| game->player.is_moving)
	{
		animate_player_utils(game, prev_x, prev_y);
		if (game->player.direction < 0 || game->player.direction >= 4)
			game->player.direction = 0;
		if (game->player.current_frame < 0 || game->player.current_frame >= 3)
			game->player.current_frame = 0;
		current_sprite = game->player.sprites
		[game->player.direction][game->player.current_frame];
		if (current_sprite)
			mlx_put_image_to_window(game->mlx, game->win, current_sprite,
				game->player.x, game->player.y);
		prev_x = game->player.x;
		prev_y = game->player.y;
	}
}
