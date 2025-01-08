/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 23:37:14 by ledio             #+#    #+#             */
/*   Updated: 2024/12/22 02:22:28 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_rows(char *filename)
{
	char		c;
	int			row;
	int			fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error("Error: Failed to open the file");
	row = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
			row++;
	}
	close(fd);
	return (row);
}

int	get_col(char *filename)
{
	int		col;
	char	c;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error("Error: Failed to open the file");
	col = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
			break ;
		col++;
	}
	close(fd);
	return (col);
}

void	load_map(char *filename, t_game *game)
{
	int			fd;
	char		*line;

	game->map.row = get_rows(filename);
	game->map.map = malloc(sizeof(char *) * (game->map.row + 1));
	if (!game->map.map)
		return ;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error("Error: Opening the file");
	game->i = -1;
	while (++game->i < game->map.row)
	{
		line = get_next_line(fd);
		if (line)
		{
			if (line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			game->map.map[game->i] = ft_strdup(line);
			free (line);
		}
	}
	game->map.map[game->i] = NULL;
	game->map.col = get_col(filename);
	close(fd);
}
