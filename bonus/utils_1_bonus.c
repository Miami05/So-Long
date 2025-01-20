/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:58:42 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/20 12:59:25 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	render_shadow(t_game *game, int x, int y, char *text)
{
	float		offset;

	offset = 1.2;
	mlx_string_put(game->mlx, game->win, x - offset, y - offset,
		0x000000, text);
	mlx_string_put(game->mlx, game->win, x + offset, y - offset,
		0x000000, text);
	mlx_string_put(game->mlx, game->win, x - offset, y + offset,
		0x000000, text);
	mlx_string_put(game->mlx, game->win, x + offset, y + offset,
		0x000000, text);
}

char	*generate_coins_string(t_game *game, char *moves_str)
{
	char	*tmp1;
	char	*tmp2;
	char	*coins_str;

	tmp1 = ft_itoa(game->player.collected_coins);
	tmp2 = ft_itoa(game->player.max_coins);
	if (!tmp1 || !tmp2)
	{
		free(moves_str);
		free(tmp1);
		free(tmp2);
		return (NULL);
	}
	coins_str = ft_strjoin(tmp1, "/");
	free(tmp1);
	if (coins_str)
	{
		tmp1 = coins_str;
		coins_str = ft_strjoin(coins_str, tmp2);
		free(tmp1);
	}
	free(tmp2);
	return (coins_str);
}

void	render_stats_text(t_game *game, int text_base, char *moves_str,
	char *coins_str)
{
	render_shadow(game, text_base, 20, "Moves:");
	render_shadow(game, text_base + 70, 20, moves_str);
	render_shadow(game, text_base, 45, "Coins:");
	render_shadow(game, text_base + 70, 45, coins_str);
	mlx_string_put(game->mlx, game->win, text_base, 20, 0xFFFFFF, "Moves:");
	mlx_string_put(game->mlx, game->win, text_base + 70, 20,
		0xFFFFFF, moves_str);
	mlx_string_put(game->mlx, game->win, text_base, 45, 0xFFFFFF, "Coins:");
	mlx_string_put(game->mlx, game->win, text_base + 70, 45,
		0xFFFFFF, coins_str);
}

void	render_game_stats(t_game *game)
{
	char	*moves_str;
	char	*coins_str;
	int		text_base;

	moves_str = ft_itoa(game->player.moves);
	if (!moves_str)
		return ;
	coins_str = generate_coins_string(game, moves_str);
	if (!coins_str)
		return ;
	text_base = (game->map.col * TILE_SIZE) - 100;
	render_stats_text(game, text_base, moves_str, coins_str);
	free(moves_str);
	free(coins_str);
}
