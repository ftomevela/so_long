/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity_jump.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftome-ve <ftome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:10:53 by ftome-ve          #+#    #+#             */
/*   Updated: 2024/06/27 15:53:29 by ftome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	gravity(t_var *var, int new_x, int new_y)
{
	new_y = var->map.player_y + 1;
	while (new_y < var->map.height && (var->map.file[new_y][new_x] == '0'
		|| var->map.file[new_y][new_x] == 'C'))
	{
		move(var, new_y, new_x, 1);
		new_y = var->map.player_y + 1;
	}
}

void	jump_2(t_var *var, int new_x, int new_y)
{
	if (var->jump_direction == 'L')
		new_x = new_x - 1;
	else if (var->jump_direction == 'R')
		new_x = new_x + 1;
	if (new_x < 0 || new_x >= var->map.width
		|| var->map.file[var->map.player_y][new_x] == '1')
		new_x = var->map.player_x;
	new_y = var->map.player_y + 1;
	if (new_y < var->map.height && (var->map.file[new_y][new_x] == '0'
		|| var->map.file[new_y][new_x] == 'C'))
	{
		move(var, new_y, new_x, 1);
	}
	else
		var->is_jumping = 0;
}

void	jump_1(t_var *var)
{
	var->is_jumping = 0;
	var->jump_count++;
	if (var->jump_count < 100)
	{
		var->is_jumping = 1;
		var->jump_progress = 0;
	}
	else
		var->jump_count = 0;
}

void	jump(t_var *var, int new_x, int new_y)
{
	new_y = var->map.player_y - 1;
	if (new_y >= 0 && (var->map.file[new_y][new_x] == '0'
		|| var->map.file[new_y][new_x] == 'C')
		&& var->jump_progress < var->jump_height)
	{
		move(var, new_y, new_x, 1);
		var->jump_progress++;
	}
	else
		jump_1(var);
}

void	apply_gravity(t_var *var)
{
	int	new_x;
	int	new_y;

	new_x = var->map.player_x;
	new_y = var->map.player_y;
	if (var->is_jumping)
	{
		if (var->jump_delay < var->jump_max_delay)
		{
			var->jump_delay++;
			return ;
		}
		var->jump_delay = 0;
		if (var->jump_progress < var->jump_height)
			jump(var, new_x, new_y);
		else
			jump_2(var, new_x, new_y);
	}
	else
		gravity(var, new_x, new_y);
	image_draw(var);
}
