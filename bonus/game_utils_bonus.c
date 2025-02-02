/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:02:36 by ldurmish          #+#    #+#             */
/*   Updated: 2025/02/01 14:32:58 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	handle_movement(t_game *game, int new_x,
	int new_y, int direction)
{
	game->moves.x = new_x;
	game->moves.y = new_y;
	game->moves.new_grid_x = game->moves.x / TILE_SIZE;
	game->moves.new_grid_y = game->moves.y / TILE_SIZE;
	if (is_valid_move(game, game->moves.new_grid_x, game->moves.new_grid_y))
	{
		move_player(game, game->moves.new_grid_x, game->moves.new_grid_y);
		game->player.direction = direction;
		game->player.is_moving = true;
	}
}

static void	player_coordinates(t_game *game)
{
	game->moves.x = game->player.x;
	game->moves.y = game->player.y;
	game->moves.grid_x = game->moves.x / TILE_SIZE;
	game->moves.grid_y = game->moves.y / TILE_SIZE;
}

static bool	handle_movement_keys(int keycode, t_game *game)
{
	game->player.is_moving = false;
	if (keycode == KEY_W || keycode == KEY_UP)
	{
		handle_movement(game, game->player.x, game->player.y - TILE_SIZE, 3);
		return (true);
	}
	else if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		handle_movement(game, game->player.x, game->player.y + TILE_SIZE, 0);
		return (true);
	}
	else if (keycode == KEY_A || keycode == KEY_LEFT)
	{
		handle_movement(game, game->player.x - TILE_SIZE, game->player.y, 1);
		return (true);
	}
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		handle_movement(game, game->player.x + TILE_SIZE, game->player.y, 2);
		return (true);
	}
	return (false);
}

static bool	handle_special_keys(int keycode, t_game *game)
{
	if (keycode == KEY_SPACE)
	{
		place_bomb(game);
		return (true);
	}
	else if (keycode == KEY_ESC)
	{
		exit_game(game);
		return (true);
	}
	return (false);
}

int	key_press(int keycode, t_game *game)
{
	if (!game)
		return (0);
	player_coordinates(game);
	if (handle_movement_keys(keycode, game))
		return (0);
	handle_special_keys(keycode, game);
	return (0);
}
