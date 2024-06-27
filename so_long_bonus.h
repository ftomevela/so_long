/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftome-ve <ftome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:30:06 by ftome-ve          #+#    #+#             */
/*   Updated: 2024/06/26 15:48:10 by ftome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# define BUFFER_SIZE 10000
# define TILE_SIZE 50
# define WON 150

# include "mlx/mlx.h"
# include <stdlib.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <X11/X.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/time.h>

typedef struct s_img
{
	void	*wall;
	void	*floor;
	void	*collectable;
	void	*player;
	void	*player_left;
	void	*player_right;
	void	*ghost;
	void	*img_ptr;
	void	*exit;
	void	*exitopen;
	void	*counter_box;
	void	*you_won;
}			t_img;

typedef struct s_map
{
	char	**file;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		total_c;
	int		total_p;
	int		total_e;
	int		collected_c;
	int		found_exit;
	char	**map_copy;
	int		ghost_x;
	int		ghost_y;
	char	ghost_direction;
}			t_map;

typedef struct s_var
{
	void			*mlx_prt;
	void			*win_ptr;
	t_map			map;
	t_img			img;
	int				counter;
	int				collec;
	int				is_jumping;
	int				jump_height;
	int				jump_progress;
	int				jump_count;
	char			jump_direction;
	char			player_direction;
	int				jump_delay;
	int				jump_max_delay;
	int				won;
	double			e_move_time;
	double			e_accum_time;
	struct timeval	last_update;
	struct timeval	now;
}			t_var;

//*************ERRORS*************************//
void	map_error(char *s);
int		is_wrong_file(char *arch_ext);
int		end_game(t_var *var);
void	free_map(char **map, t_var *var);
int		valid_map_walls(char **map, int width, int height);
int		check_valid_path(t_var *var);
char	*free_mode(char *s1, char *s2, int mode);
void	show_on_terminal(char *c);

//***************OTHERS**************************//
int		ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2, int mode);
char	*ft_itoa(int n);

//***********get_next_line / utils*****************//
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
int		ft_strlen(const char *s);
//char	*ft_strjoin(char *s1, char *s2);
void	*ft_calloc(size_t num_elements, size_t element_size);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *str);
char	*funtion_read( char *line, int fd);
char	*ft_nextline(char *line);

//**************graphics********************//
void	image_draw(t_var *var);
void	draw_background(t_var *var);
char	**load_map(char *game_file, int *width, int *height);
int		count_lines(char *game_file);
void	draw_walls(t_var *var);
void	init_image(t_var *var);
void	draw_counter_box(t_var *var);
void	put_image(t_var *var, t_var *image, int x, int y);
void	init_variables(t_var *var);
void	draw_collectibles(t_var *var);

//***************movements***************//
int		movement_check(t_var *var, int new_x, int new_y);
void	move(t_var *var, int new_y, int new_x, int jump);
void	apply_gravity(t_var *var);
int		handle_key(int Keysym, t_var *var);
void	move_ghost(t_var *var);
void	delta_time(void *vdata);
void	init_jump(t_var *var);

#endif
