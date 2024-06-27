/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftome-ve <ftome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:11:58 by ftome-ve          #+#    #+#             */
/*   Updated: 2024/06/25 15:28:55 by ftome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ghost_right(t_var *var, int x, int y)
{
	if (x + 1 < var->map.width && var->map.file[y][x + 1] != '1')
	{
		x++;
		if (var->map.file[y][x - 1] == 'C')
			put_image(var, var->img.collectable, x - 1, y);
		if (var->map.file[y][x - 1] == '0')
			put_image(var, var->img.floor, x - 1, y);
	}
	else
	{
		var->map.ghost_direction = 'L';
		if (x - 1 >= 0 && var->map.file[y][x - 1] != '1')
		{
			x--;
			if (var->map.file[y][x + 1] == 'C')
				put_image(var, var->img.collectable, x + 1, y);
			if (var->map.file[y][x + 1] == '0')
				put_image(var, var->img.floor, x + 1, y);
		}
	}
	return (x);
}

int	ghost_left(t_var *var, int x, int y)
{
	if (x - 1 >= 0 && var->map.file[y][x - 1] != '1')
	{
		x--;
		if (var->map.file[y][x + 1] == 'C')
			put_image(var, var->img.collectable, x + 1, y);
		if (var->map.file[y][x + 1] == '0')
			put_image(var, var->img.floor, x + 1, y);
	}
	else
	{
		var->map.ghost_direction = 'R';
		if (x + 1 < var->map.width && var->map.file[y][x + 1] != '1')
		{
			x++;
			if (var->map.file[y][x - 1] == 'C')
				put_image(var, var->img.collectable, x - 1, y);
			if (var->map.file[y][x - 1] == '0')
				put_image(var, var->img.floor, x - 1, y);
		}
	}
	return (x);
}

void	move_ghost(t_var *var)
{
	int	x;
	int	y;
	int	new_y;

	new_y = var->map.ghost_y;
	x = var->map.ghost_x;
	y = var->map.ghost_y;
	if (var->map.ghost_direction == 'R')
	{
		x = ghost_right(var, x, y);
	}
	else if (var->map.ghost_direction == 'L')
	{
		x = ghost_left(var, x, y);
	}
	var->map.ghost_x = x;
	var->map.ghost_y = y;
	if (x == var->map.player_x && y == var->map.player_y)
	{
		show_on_terminal("Game over\n");
		end_game(var);
	}
	image_draw(var);
}

void	draw_counter_box(t_var *var)
{
	char	*counter_text;
	int		box_x;
	int		box_y;

	box_x = 1800;
	box_y = 250;
	mlx_put_image_to_window(var->mlx_prt, var->win_ptr, var->img.counter_box,
		box_x, box_y);
	counter_text = ft_strjoin("Movements: ", ft_itoa(var->counter), 2);
	mlx_string_put(var->mlx_prt, var->win_ptr, box_x + 10,
		box_y + 20, 0xFFFFFF, counter_text);
	show_on_terminal(counter_text);
	free(counter_text);
	counter_text = ft_strjoin("Collectibles: ", ft_itoa(var->collec), 2);
	mlx_string_put(var->mlx_prt, var->win_ptr, box_x + 10, box_y + 40, 0xFFFFFF,
		counter_text);
	free(counter_text);
}
