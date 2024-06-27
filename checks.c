/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftome-ve <ftome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:42:29 by ftome-ve          #+#    #+#             */
/*   Updated: 2024/06/27 17:51:55 by ftome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_valid_numbers(t_var *var)
{
	int	i;
	int	j;

	i = 0;
	while (i < var->map.height)
	{
		j = 0;
		while (j < var->map.width)
		{
			if (var->map.file[i][j] == 'C')
				var->map.total_c++;
			if (var->map.file[i][j] == 'P')
			{
				var->map.player_y = i;
				var->map.player_x = j;
				var->map.total_p++;
			}
			if (var->map.file[i][j] == 'E')
				var->map.total_e++;
			j++;
		}
		i++;
	}
	if (var->map.total_p > 1 || var->map.total_e > 1)
		map_error("there is more than 1 player or exit");
}

void	floodfill(t_var *var, int start_x, int start_y)
{
	int	height;
	int	width;

	height = var->map.height;
	width = var->map.width;
	if (start_x < 0 || start_x >= width || start_y < 0 || start_y >= height
		|| var->map.map_copy[start_y][start_x] == '1'
		|| var->map.map_copy[start_y][start_x] == 'V')
		return ;
	if (var->map.map_copy[start_y][start_x] == 'C')
		var->map.collected_c++;
	if (var->map.map_copy[start_y][start_x] == 'E')
		var->map.found_exit = 1;
	var->map.map_copy[start_y][start_x] = 'V';
	floodfill(var, start_x + 1, start_y);
	floodfill(var, start_x - 1, start_y);
	floodfill(var, start_x, start_y + 1);
	floodfill(var, start_x, start_y - 1);
}

void	copy_map(t_var *var, int i)
{
	int	j;

	var->map.map_copy[i] = (char *)malloc((var->map.width + 1) * sizeof(char));
	if (var->map.map_copy[i] == NULL)
		exit(EXIT_FAILURE);
	j = 0;
	while (j < var->map.width)
	{
		var->map.map_copy[i][j] = var->map.file[i][j];
		j++;
	}
	var->map.map_copy[i][var->map.width] = '\0';
}

int	check_valid_path(t_var *var)
{
	int	i;

	i = 0;
	check_valid_numbers(var);
	var->map.map_copy = (char **)malloc((var->map.height + 1)
			* sizeof (char *));
	if (var->map.map_copy == NULL)
		exit(EXIT_FAILURE);
	while (i < var->map.height)
	{
		copy_map(var, i);
		i++;
	}
	var->map.map_copy[i] = NULL;
	floodfill(var, var->map.player_x, var->map.player_y);
	free_map(var->map.map_copy, var);
	if (var->map.collected_c == var->map.total_c && var->map.found_exit == 1
		&& var->map.total_p == 1)
		return (1);
	else
		return (0);
}

int	is_wrong_file(char *arch_ext)
{
	int	len;

	len = ft_strlen(arch_ext) - 1;
	if (arch_ext[len] == 'r' && arch_ext[len - 1] == 'e'
		&& arch_ext[len - 2] == 'b' && arch_ext[len - 3] == '.')
		return (0);
	else
	{
		return (1);
	}
}
