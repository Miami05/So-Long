/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:02:36 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/17 15:02:54 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	player_new_grid_coordinates(t_game *game)
{
	game->moves.new_grid_x = game->moves.x / TILE_SIZE;
	game->moves.new_grid_y = game->moves.y / TILE_SIZE;
	if (is_valid_move(game, game->moves.new_grid_x, game->moves.new_grid_y))
		move_player(game, game->moves.new_grid_x, game->moves.new_grid_y);
}

static void	player_coordinates(t_game *game)
{
	game->moves.x = game->player.x;
	game->moves.y = game->player.y;
	game->moves.grid_x = game->moves.x / TILE_SIZE;
	game->moves.grid_y = game->moves.y / TILE_SIZE;
}

bool	key_press_utils(int keycode, t_game *game)
{
	if (keycode == KEY_W)
	{
		game->moves.y -= TILE_SIZE;
		game->player.direction = 3;
		return (true);
	}
	else if (keycode == KEY_S)
	{
		game->moves.y += TILE_SIZE;
		game->player.direction = 0;
		return (true);
	}
	else if (keycode == KEY_A)
	{
		game->moves.x -= TILE_SIZE;
		game->player.direction = 1;
		return (true);
	}
	else if (keycode == KEY_D)
	{
		game->moves.x += TILE_SIZE;
		game->player.direction = 2;
		return (true);
	}
	return (false);
}

int	key_press(int keycode, t_game *game)
{
	bool	key_movement;

	key_movement = false;
	player_coordinates(game);
	if (key_press_utils(keycode, game))
	{
		game->player.is_moving = true;
		key_movement = true;
	}
	else if (keycode == KEY_SPACE)
		place_bomb(game);
	else if (keycode == KEY_ESC)
		exit_game(game);
	if (key_movement)
		player_new_grid_coordinates(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_A || keycode == KEY_D || keycode == KEY_S
		|| keycode == KEY_W)
		game->player.is_moving = false;
	return (0);
}
