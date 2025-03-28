/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:08:53 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/28 18:15:21 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// get the index of the texture that will be drawn on screen
static mlx_texture_t	*get_wall_text(t_ray ray, t_cub *cub)
{
	if (ray.side == 1 && ray.ray_dir_y < 0)
		return (cub->no_xpm);
	else if (ray.side == 1 && ray.ray_dir_y > 0)
		return (cub->so_xpm);
	else if (ray.side == 0 && ray.ray_dir_x > 0)
		return (cub->ea_xpm);
	else
		return (cub->we_xpm);
}

static void calculate_texture_params(t_cub *cub, t_ray ray, t_draw *draw, mlx_texture_t *texture)
{
	int tex_width;

	// Récupérer la texture associée au mur
	// Calculer la position exacte du rayon sur le mur
	if (ray.side == 0)
		draw->wall_x = cub->player.pos_y + ray.perp_wall_dist * ray.ray_dir_y;
	else
		draw->wall_x = cub->player.pos_x + ray.perp_wall_dist * ray.ray_dir_x;

	// Fractionner la position pour obtenir la partie décimale
	draw->wall_x -= floor(draw->wall_x);

	// Calculer la coordonnée X de la texture
	tex_width = texture->width;
	draw->tex_x = (int)(draw->wall_x * tex_width);

	// Si on regarde un mur à droite ou en haut, on inverse la coordonnée X
	if ((ray.side == 0 && ray.ray_dir_x > 0) || (ray.side == 1 && ray.ray_dir_y < 0))
		draw->tex_x = tex_width - draw->tex_x - 1;

	// Calculer la quantité à incrémenter pour chaque pixel de l'écran
	if (ray.draw_end - ray.draw_start != 0)
		draw->step = 1.0 * texture->height / (ray.draw_end - ray.draw_start);
	else
		draw->step = 0; // Eviter la division par 0 si draw_end == draw_start (précaution)

	// Initialiser tex_pos pour le premier pixel de l'écran
	draw->tex_pos = (ray.draw_start - cub->win_height / 2 + (ray.draw_end - ray.draw_start) / 2) * draw->step;
}

void draw_wall(t_cub *cub, int x, t_ray ray)
{
	t_draw draw;
	mlx_texture_t *texture;
	int y;

	texture = get_wall_text(ray, cub);
	calculate_texture_params(cub, ray, &draw, texture);
	y = ray.draw_start;

	while (y < ray.draw_end)
	{
		// Calculer la coordonnée Y de la texture
		draw.tex_y = (int)draw.tex_pos & (texture->height - 1); // Limiter à la hauteur de la texture
		draw.tex_pos += draw.step;

		// Calculer la couleur du pixel à partir de la texture
		draw.color = get_texture_color(texture, draw.tex_x, draw.tex_y);

		// Assombrir les murs Nord et Sud (en fonction de la direction)
		if (ray.side == 1) // Si c'est un mur nord/sud (selon les calculs raycast)
			draw.color = (draw.color >> 1) & 8355711;

		// Dessiner le pixel
		mlx_put_pixel(cub->img_ptr, x, y, draw.color);
		y++;
	}
}


// draw the ceilling in the first half of the screen using :
// cub->ceilling.red;
// cub->ceilling.green;
// cub->ceilling.blue;
void	draw_ceilling(t_cub *cub)
{
	int			y;
	int			x;
	int32_t		color;

	color = (cub->ceil.red << 16) | (cub->ceil.green << 8) | cub->ceil.blue;
	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			mlx_put_pixel(cub->img_ptr, x, y, color);
			x++;
		}
		y++;
	}
}

// draw the floor in the second half of the screen using :
// cub->floor.red;
// cub->floor.green;
// cub->floor.blue;
void	draw_floor(t_cub *cub)
{
	int			y;
	int			x;
	int32_t		color;

	color = (cub->floor.red << 16) | (cub->floor.green << 8) | cub->floor.blue;
	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			mlx_put_pixel(cub->img_ptr, x, y, color);
			x++;
		}
		y++;
	}
}
