/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:03:25 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/29 00:04:38 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	my_mlx_pixel_put(t_global *global, int x, int y, int color)
{
	char	*dst;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	if (!global || !global->mlx_image || x < 0 || x >= S_W || y < 0 || y >= S_H)
		return ;
	dst = mlx_get_data_addr(global->mlx_image, &bits_per_pixel, &line_length,
			&endian);
	if (!dst)
		return ;
	dst = dst + (y * line_length + x * (bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_texture	*get_texture_index(t_global *global)
{
	float	angle;

	angle = global->ray->angle;
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	if (global->ray->ray_f == 1)
	{
		if (angle > M_PI && angle < 2 * M_PI)
			return (global->data->north_tex);
		else
			return (global->data->south_tex);
	}
	else
	{
		if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
			return (global->data->west_tex);
		else
			return (global->data->east_tex);
	}
}

int	get_check_x(t_global *global)
{
	int			tex_x;

	if (global->ray->ray_f == 1)
		tex_x = global->ray->horiz_x - (int)(global->ray->horiz_x / TILE_SIZE)
			* TILE_SIZE;
	else
		tex_x = global->ray->vert_y - (int)(global->ray->vert_y / TILE_SIZE)
			* TILE_SIZE;
	tex_x = (int)(tex_x * global->img->width / TILE_SIZE);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= global->img->width)
		tex_x = global->img->width - 1;
	return (tex_x);
}

void	draw_wall(t_global *global, int ray, int t_pix, int b_pix)
{
	int			y;
	int			d;
	int			tex_x;
	int			tex_y;
	int			*addr;

	y = t_pix;
	global->img = get_texture_index(global);
	tex_x = get_check_x(global);
	while (y < b_pix)
	{
		d = y + (global->data->wall_h / 2) - S_H / 2;
		tex_y = (d * global->img->height) / global->data->wall_h;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= global->img->height)
			tex_y = global->img->height - 1;
		addr = (int *)global->img->addr;
		global->data->color = addr[tex_y * global->img->width + tex_x];
		my_mlx_pixel_put(global, ray, y, global->data->color);
		y++;
	}
}

void	render_wall(int ray)
{
	t_global	*global;
	double		wall_h;
	double		t_pix;
	double		b_pix;

	global = *get_heap();
	global->ray->distance *= cos(global->ray->angle - global->player->angle);
	wall_h = (TILE_SIZE / global->ray->distance) * ((S_W / 2)
			/ tan(global->player->fov / 2));
	global->data->wall_h = wall_h;
	b_pix = (S_H / 2) + (wall_h / 2);
	t_pix = (S_H / 2) - (wall_h / 2);
	if (b_pix > S_H)
		b_pix = S_H;
	if (t_pix < 0)
		t_pix = 0;
	draw_wall(global, ray, t_pix, b_pix);
	draw_floor_ceiling(global, ray, t_pix, b_pix);
}
