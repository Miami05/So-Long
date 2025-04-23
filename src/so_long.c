/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 23:11:47 by ledio             #+#    #+#             */
/*   Updated: 2025/04/23 23:31:53 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	is_ber_file(const char *filename)
{
	int		len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	return (ft_strncmp(filename + len - 4, ".ber", 4) == 0);
}

int	game_loop(t_game *game)
{
	static int		frame_count = 0;

	if (!game || !game->mlx || !game->win)
		return (0);
	render_map(game);
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
	game->coins.anim_speed = 240;
	game->player.coins_needed = 3;
}

void	init_map_utils(t_game *game)
{
	init_vars(game);
	validate_map(game);
	init_player(game);
	load_texture(game);
}

int	main(int argc, char *argv[])
{
	t_game		game;

	if (argc != 2)
		return (ft_printf("Usage: ./so_long <maps/map.ber>\n"));
	if (!is_ber_file(argv[1]))
		return (ft_printf("Error: The file must have .ber extensions\n"));
	initialize_game(&game);
	game.mlx = mlx_init();
	if (!game.mlx)
		error("Error: MLX initialization failed", &game);
	load_map(argv[1], &game);
	if (!is_map_valid_size(&game))
	{
		ft_printf("Error: Map size exceeds resolution\n"),
		exit_game(&game);
	}
	init_map_utils(&game);
	game.win = mlx_new_window(game.mlx, game.map.col
			* TILE_SIZE, game.map.row * TILE_SIZE, "so_long");
	if (!game.win)
	{
		ft_printf("Error: Loading the map");
		exit_game(&game);
	}
	setup_game_tools(&game);
	if (mlx_loop(game.mlx) == KEY_ESC)
		exit_game(&game);
}
