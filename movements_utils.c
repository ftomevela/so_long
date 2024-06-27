/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftome-ve <ftome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:11:58 by ftome-ve          #+#    #+#             */
/*   Updated: 2024/06/27 14:43:19 by ftome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
