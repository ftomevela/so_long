/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftome-ve <ftome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:18:45 by ftome-ve          #+#    #+#             */
/*   Updated: 2024/06/26 13:53:15 by ftome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_background(t_var *var)
{
	int	x;
	int	y;

	y = 0;
	while (y < var->map.height * TILE_SIZE)
	{
		x = 0;
		while (x < var->map.width * TILE_SIZE)
		{
			mlx_put_image_to_window(var->mlx_prt, var->win_ptr,
				var->img.floor, x, y);
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}
}

void	draw_walls(t_var *var)
{
	int		y;
	int		x;

	y = 0;
	var->counter = 0;
	while (y < var->map.height)
	{
		x = 0;
		while (var->map.file[y][x])
		{
			if (var->map.file[y][x] == '1')
				put_image(var, var->img.wall, x, y);
			x++;
		}
		y++;
	}
}

void	draw_collectibles(t_var *var)
{
	int		y;
	int		x;

	y = 0;
	while (y < var->map.height)
	{
		x = 0;
		while (var->map.file[y][x])
		{
			if (var->map.file[y][x] == 'C')
			{
				put_image(var, var->img.collectable, x, y);
				var->collec++;
			}
			x++;
		}
		y++;
	}
}

void	drawing(t_var *var, int y)
{
	int	x;

	x = 0;
	while (var->map.file[y][x])
	{
		if (var->map.file[y][x] == 'P')
		{
			put_image(var, var->img.player, x, y);
			var->map.player_y = y;
			var->map.player_x = x;
		}
		if (var->map.file[y][x] == 'E')
		{
			if (var->collec == 0)
				put_image(var, var->img.exitopen, x, y);
			else
				put_image(var, var->img.exit, x, y);
		}
		x++;
	}
}

void	image_draw(t_var *var)
{
	int	y;

	y = 0;
	while (y < var->map.height)
	{
		drawing(var, y);
		y++;
	}
}
