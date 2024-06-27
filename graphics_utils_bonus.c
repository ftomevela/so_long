/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftome-ve <ftome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:23:12 by ftome-ve          #+#    #+#             */
/*   Updated: 2024/06/25 15:28:27 by ftome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_variables(t_var *var)
{
	var->jump_height = 10;
	var->map.ghost_direction = 'L';
	var->e_move_time = 0.2;
	var->e_accum_time = 0.050;
}

void	*load_img(t_var *var, char *path)
{
	int		y;
	int		x;
	void	*temp;

	temp = mlx_xpm_file_to_image(var->mlx_prt, path, &x, &y);
	if (!temp)
	{
		write (2, "Error\n\nfailed to  load texture\n", 32);
		end_game(var);
	}
	return (temp);
}

void	init_image(t_var *var)
{
	var->img.floor = load_img(var, "g_images/f_sp.xpm");
	var->img.wall = load_img(var, "g_images/w_sp.xpm");
	var->img.exit = load_img(var, "g_images/e_sp.xpm");
	var->img.counter_box = load_img(var, "g_images/cb_sp.xpm");
	var->img.exitopen = load_img(var, "g_images/e_open_sp.xpm");
	var->img.collectable = load_img(var, "g_images/c_sp.xpm");
	var->img.player = load_img(var, "g_images/p_sp.xpm");
	var->img.player_left = load_img(var, "g_images/p_left_sp.xpm");
	var->img.player_right = load_img(var, "g_images/p_right_sp.xpm");
	var->img.you_won = load_img(var, "g_images/yw_sp.xpm");
}

void	put_image(t_var *var, t_var *image, int x, int y)
{
	mlx_put_image_to_window(var->mlx_prt, var->win_ptr, image,
		x * TILE_SIZE, y * TILE_SIZE);
}
