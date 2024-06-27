/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftome-ve <ftome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:04:18 by ftome-ve          #+#    #+#             */
/*   Updated: 2024/06/25 19:05:17 by ftome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	loop_hook(t_var *var)
{
	apply_gravity(var);
	delta_time(var);
	return (0);
}

void	init_game(t_var *var, char *game_file)
{
	var->mlx_prt = mlx_init();
	if (var->mlx_prt == NULL)
		end_game(var);
	var->map.file = load_map(game_file, &var->map.width, &var->map.height);
	if (var->map.file == NULL)
		end_game(var);
	if (!valid_map_walls(var->map.file, var->map.width, var->map.height))
		map_error("Map is not surronded by walls");
	if (!check_valid_path(var))
		map_error("There is not a valid path");
	var->win_ptr = mlx_new_window(var->mlx_prt, var->map.width * 50,
			var->map.height * 50, "MI JUEGO");
	if (var->win_ptr == NULL)
		end_game(var);
	init_image(var);
	draw_background(var);
	draw_walls(var);
	draw_counter_box(var);
	draw_collectibles(var);
	image_draw(var);
	mlx_key_hook(var->win_ptr, handle_key, var);
	mlx_hook(var->win_ptr, DestroyNotify, 0, end_game, var);
	mlx_loop_hook(var->mlx_prt, loop_hook, var);
}

void	delta_time(void *vdata)
{
	t_var	*var;
	double	dif_sec;
	double	dif_mcsec;

	var = vdata;
	gettimeofday(&var->now, NULL);
	dif_sec = (var->now.tv_sec - var->last_update.tv_sec);
	dif_mcsec = (var->now.tv_usec - var->last_update.tv_usec) / 1000000.0;
	var->e_accum_time += dif_sec + dif_mcsec;
	if (var->e_accum_time >= var->e_move_time)
	{
		move_ghost(var);
		var->e_accum_time = 0.0;
	}
	var->last_update = var->now;
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = b;
	while (len > 0)
	{
		*ptr++ = c;
		len--;
	}
	return (b);
}

int	main(int argc, char *argv[])
{
	t_var	var;

	ft_memset(&var, 0, sizeof(t_var));
	if (argc == 1)
		map_error("no map specified");
	else if (argc > 2)
		map_error("too many arguments");
	else if (argc == 2 && is_wrong_file(argv[1]))
		map_error("map file must be a .ber file");
	init_variables(&var);
	init_game(&var, argv[1]);
	mlx_loop(var.mlx_prt);
}
