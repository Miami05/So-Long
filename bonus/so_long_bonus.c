/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:29:54 by ldurmish          #+#    #+#             */
/*   Updated: 2025/02/21 20:32:27 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	game_loop(t_game *game)
{
	static int		frame_count = 0;

	if (!game || !game->mlx || !game->win)
		return (0);
	if (game->bomb.active)
	{
		update_bomb_state(game);
		if (!game->bomb.is_exploding && frame_count % 5 == 0)
		{
			game->bomb.current_frame = (game->bomb.current_frame + 1) % 4;
			render_bomb(game);
		}
	}
	render_map(game);
	render_enemy(game);
	render_game_stats(game);
	frame_count = (frame_count + 1) % 1000;
	return (0);
}

void	initialize_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->player.direction = 0;
	game->width = TILE_SIZE;
	game->height = TILE_SIZE;
	game->player.is_moving = false;
	game->player.current_frame = 1;
	game->player.explosion_power = 1;
	game->coins.anim_speed = 100;
	game->player.coins_needed = 3;
}

void	init_map_utils(t_game *game)
{
	init_vars(game);
	validate_map(game);
	init_player(game);
	init_enemy_map(game);
	load_texture(game);
}

int	main(int argc, char *argv[])
{
	t_game		game;

	if (argc != 2)
		error("Usage: ./so_long <maps/map.ber>");
	initialize_game(&game);
	game.mlx = mlx_init();
	if (!game.mlx)
		error("Error: MLX initialization failed");
	load_map(argv[1], &game);
	if (!is_map_valid_size(&game))
	{
		ft_printf("Error: Map size exceeds resolution\n");
		exit_game(&game);
	}
	init_map_utils(&game);
	game.win = mlx_new_window(game.mlx, game.map.col * TILE_SIZE,
			game.map.row * TILE_SIZE, "so_long");
	if (!game.win)
	{
		ft_printf("Error: Loading the map");
		exit_game(&game);
	}
	setup_game_tools(&game);
	if (mlx_loop(game.mlx) == KEY_ESC)
		exit_game(&game);
}
