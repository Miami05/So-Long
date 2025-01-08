/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 23:11:47 by ledio             #+#    #+#             */
/*   Updated: 2024/12/22 20:17:44 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game		game;

	if (argc != 2)
		error("Usage: ./so_long <maps/map.ber>");
	init_vars(&game);
	game.mlx = mlx_init();
	if (!game.mlx)
		error("Error: MLX initialization failed");
	load_map(argv[1], &game);
	validate_map(&game);
	init_player(&game);
	load_texture(&game);
	game.win = mlx_new_window(game.mlx, game.map.col * TILE_SIZE,
			game.map.row * TILE_SIZE, "so_long");
	if (!game.win)
		error("Error: Loading the map");
	setup_game_tools(&game);
	if (mlx_loop(game.mlx) == KEY_ESC)
		exit_game(&game);
}
