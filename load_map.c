/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftome-ve <ftome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:13:39 by ftome-ve          #+#    #+#             */
/*   Updated: 2024/06/27 18:26:46 by ftome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(char *game_file)
{
	int		lines;
	int		fd;
	char	*line;

	lines = 0;
	fd = open(game_file, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

char	**load_map(char *game_file, int *width, int *height)
{
	int		fd;
	int		i;
	char	**map;
	char	*file;

	i = 0;
	fd = open(game_file, O_RDONLY);
	if (fd < 0)
		exit (1);
	*height = count_lines(game_file);
	if (*height <= 0)
		return (NULL);
	map = malloc((sizeof (char *)) * (*height + 1));
	if (map == NULL)
		return (NULL);
	file = get_next_line(fd);
	*width = ft_strlen(file) - 1;
	while (file)
	{
		map[i++] = file;
		file = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void	free_map(char **map, t_var	*var)
{
	int	i;

	i = 0;
	while (i < var->map.height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
