/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftome-ve <ftome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:22:54 by ftome-ve          #+#    #+#             */
/*   Updated: 2024/06/27 18:26:20 by ftome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	you_won(t_var *var, int new_y, int new_x)
{
	var->won = 1;
	var->map.file[new_y][new_x] = 'E';
	var->map.file[var->map.player_y][var->map.player_x] = '0';
	var->map.player_x = new_x;
	var->map.player_y = new_y;
	mlx_put_image_to_window(var->mlx_prt, var->win_ptr, var->img.you_won,
		var->map.width * 50 / 2 - 150, var->map.height * 50 / 2 - 150);
	show_on_terminal("You WON!\n");
}

void	move(t_var *var, int new_y, int new_x, int jump)
{
	char	curr_tile;

	curr_tile = var->map.file[new_y][new_x];
	put_image(var, var->img.floor, var->map.player_x, var->map.player_y);
	if (curr_tile == '0' || curr_tile == 'C')
	{
		if (curr_tile == 'C')
		{
			var->collec--;
			var->map.file[new_y][new_x] = '0';
		}
		var->map.file[new_y][new_x] = 'P';
		var->map.file[var->map.player_y][var->map.player_x] = '0';
		var->map.player_x = new_x;
		var->map.player_y = new_y;
		if (jump == 0)
			var->counter++;
	}
	if (curr_tile == 'E' && var->collec == 0)
		you_won(var, new_y, new_x);
	image_draw(var);
}

int	movement_check(t_var *var, int new_x, int new_y)
{
	if (var->map.file[new_y][new_x] != '1' && var->won != 1)
	{
		move(var, new_y, new_x, 0);
		draw_counter_box(var);
		return (1);
	}
	return (0);
}

int	move_to_right(t_var *var)
{
	var->player_direction = 'R';
	if (var->is_jumping && var->jump_progress >= var->jump_height)
		var->jump_direction = 'R';
	else
	{
		movement_check(var, var->map.player_x + 1, var->map.player_y);
		return (1);
	}
	return (0);
}

int	handle_key(int Keysym, t_var *var)
{
	int	x;
	int	y;

	x = var->map.player_x;
	y = var->map.player_y;
	if (Keysym == XK_a || Keysym == XK_Left)
	{
		var->player_direction = 'L';
		if (var->is_jumping && var->jump_progress >= var->jump_height)
			var->jump_direction = 'L';
		else
			movement_check(var, x - 1, y);
	}
	else if (Keysym == XK_d || Keysym == XK_Right)
		move_to_right(var);
	else if ((Keysym == XK_w || Keysym == XK_Up) && !var->is_jumping)
		init_jump(var);
	if (Keysym == XK_s || Keysym == XK_Down)
		movement_check(var, x, y + 1);
	else if (Keysym == XK_Escape)
		end_game(var);
	apply_gravity(var);
	return (0);
}
