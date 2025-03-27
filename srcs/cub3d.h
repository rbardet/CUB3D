/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:51:13 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/27 21:46:12 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

#define WIN_HEIGHT 800
#define WIN_WIDTH 1600

#define TILE 20

#define GRAPH_HEIGHT 64
#define GRAPH_WIDTH 64

typedef int		t_bool;
#define TRUE 1
#define FALSE 0

#define M_PI 3.14159265358979323846
#define FOV_ANGLE 90

typedef struct s_rgb
{
	int			red;
	int			green;
	int			blue;
}				t_rgb;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	int			map_width;
	int			map_height;
	double		dir_x;
	double		dir_y;
	double		plane_factor;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
}				t_ray;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_cub
{
	int			win_height;
	int			win_width;
	int			g_height;
	int			g_width;
	void		*no_xpm;
	void		*so_xpm;
	void		*we_xpm;
	void		*ea_xpm;
	void		*do_xpm;
	void		*init_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		spawn_view;
	t_rgb		floor;
	t_rgb		ceil;
	t_player	player;
	t_img		**img;
	char		**map;
	t_ray		raycast;
}				t_cub;

// avoid leak
void			free_img(t_img **img);
int				free_struct(t_cub *cub);

// parsing
char			**copy_and_check_map(t_cub *cub);
int				find_max_len(char **map);
int				skip_space(char *line, int i);
t_rgb			get_rgb(char **rgb_tmp);
void			get_xpm(t_cub *cub);
t_cub			*fill_struct(t_cub *cub);
void			flood_fill(int x, int y, char **map, int *ret);
t_bool			is_one_player(char **map, int i);
t_bool			is_valid_map(t_cub *cub);
t_bool			close_or_not(char **map, int x, int y, t_cub *cub);
t_bool			is_close_map(char **map, int i, t_cub *cub);
int				count_line(char *argv);
char			**loop_copy(int fd, int nb_line);
char			**copy_map(char *argv);
t_bool			is_cub(char *map);
t_cub			*parse_struct(char *map);
t_player		init_player_struct(t_cub *cub, t_player player);

// render
void			draw_wall(t_cub *cub, int x);
void			load_texture(t_cub *cub);
void			open_window(t_cub *cub);
int				handle_keypress(int key, t_cub *cub);
int				minimap(t_cub *cub);
void			render_minimap(t_cub *cub);
void			get_draw_size(t_cub *cub);
void			ray_dist_x(t_cub *cub);
void			ray_dist_y(t_cub *cub);
void			init_ray(t_cub *cub, int x);
void			calculate_wall_heigh(t_cub *cub);
void			raycast(t_cub *cub);
t_bool			check_collision(t_cub *cub, double x, double y);
void			move_frontback(t_cub *cub, int key);
void			move_side(t_cub *cub, int key);
void			rotate_right(t_cub *cub);
void			rotate_left(t_cub *cub);
void			draw_vertical_line(t_cub *cub, int x);
void			draw_ceilling(t_cub *cub);
void			draw_floor(t_cub *cub);

// debug

//UTILS

//debug
void			print_xpm_status(void *xpm, char *name);
char			*get_direction_name(char c);
void			print_window_info(t_cub *cub);
void			print_textures_info(t_cub *cub);
void			print_colors_info(t_cub *cub);
void			print_player_info(t_cub *cub);

//debug 2
void			print_player_info(t_cub *cub);
void			print_map_info(t_cub *cub);
void			print_struct(t_cub *cub);
