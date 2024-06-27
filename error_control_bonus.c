/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_control_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftome-ve <ftome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:44:35 by ftome-ve          #+#    #+#             */
/*   Updated: 2024/06/27 18:28:45 by ftome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	map_error(char *s)
{
	int	i;

	i = 0;
	write (1, "Error.\n", 7);
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
	write (1, ".\n", 2);
	exit(EXIT_FAILURE);
}

void	destroy_image(t_var	*var)

{
	if (var->img.collectable)
		mlx_destroy_image(var->mlx_prt, var->img.collectable);
	if (var->img.player)
		mlx_destroy_image(var->mlx_prt, var->img.player);
	if (var->img.wall)
		mlx_destroy_image(var->mlx_prt, var->img.wall);
	if (var->img.floor)
		mlx_destroy_image(var->mlx_prt, var->img.floor);
	if (var->img.exit)
		mlx_destroy_image(var->mlx_prt, var->img.exit);
	if (var->img.exitopen)
		mlx_destroy_image(var->mlx_prt, var->img.exitopen);
	if (var->img.counter_box)
		mlx_destroy_image(var->mlx_prt, var->img.counter_box);
	if (var->img.you_won)
		mlx_destroy_image(var->mlx_prt, var->img.you_won);
	if (var->img.player_left)
		mlx_destroy_image(var->mlx_prt, var->img.player_left);
	if (var->img.player_right)
		mlx_destroy_image(var->mlx_prt, var->img.player_right);
}

int	end_game(t_var *var)
{
	destroy_image(var);
	if (var->map.file)
		free_map(var->map.file, var);
	if (var->win_ptr)
		mlx_destroy_window(var->mlx_prt, var->win_ptr);
	if (var->mlx_prt)
	{
		mlx_loop_end(var->mlx_prt);
		mlx_destroy_display(var->mlx_prt);
		free(var->mlx_prt);
	}
	exit (0);
}

int	check_horizontal_walls(char **map, int width, int height)
{
	int	i;

	i = 0;
	while (i < width)
	{
		if (map[0][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < width)
	{
		if (map[height - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	valid_map_walls(char **map, int width, int height)
{
	int	i;

	if (!check_horizontal_walls(map, width, height))
		return (0);
	i = 0;
	while (i < height)
	{
		if (map[i][0] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < height)
	{
		if (map[i][width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}
