/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:53:48 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/23 20:46:10 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	cleanup_gnl(int fd)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		free (tmp);
		tmp = get_next_line(fd);
	}
}

int	get_rows_utils(int read_bytes, int fd, char c, int row)
{
	int		has_char;

	has_char = 0;
	while (read_bytes > 0)
	{
		if (c == '\n')
		{
			row++;
			has_char = 0;
		}
		else
			has_char = 1;
		read_bytes = read(fd, &c, 1);
	}
	if (has_char)
		row++;
	return (row);
}

int	get_rows(char *filename, t_game *game)
{
	char		c;
	int			row;
	int			fd;
	int			read_bytes;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error("Error: Failed to open the file");
	row = 0;
	read_bytes = read(fd, &c, 1);
	if (read_bytes <= 0)
	{
		close(fd);
		ft_printf("Error: File is empty\n");
		exit_game(game);
	}
	row = get_rows_utils(read_bytes, fd, c, row);
	close(fd);
	return (row);
}

void	load_map_utils(t_game *game, char *line, int fd)
{
	while (++game->i < game->map.row)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free_map(game);
			error("Error: Failed to load the map\n");
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		game->map.map[game->i] = ft_strdup(line);
		free (line);
		if (!game->map.map[game->i])
		{
			free_map(game);
			error("Error: Memory allocation failed\n");
		}
	}
}

void	load_map(char *filename, t_game *game)
{
	int			fd;
	char		*line;

	line = NULL;
	game->map.row = get_rows(filename, game);
	game->map.col = get_col(filename);
	game->map.map = malloc(sizeof(char *) * (game->map.row + 1));
	if (!game->map.map)
		return ;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free_map(game);
		error("Error: Opening the file");
	}
	game->i = -1;
	load_map_utils(game, line, fd);
	game->map.map[game->i] = NULL;
	cleanup_gnl(fd);
	close(fd);
}
