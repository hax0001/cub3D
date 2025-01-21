/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:03:25 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/21 14:50:15 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"


// In render_wall.c, add checks:
void my_mlx_pixel_put(t_global *global, int x, int y, int color)
{
    char *dst;
    int bits_per_pixel;
    int line_length;
    int endian;

    if (!global || !global->mlx_image || x < 0 || x >= S_W || y < 0 || y >= S_H)
        return;
        
    dst = mlx_get_data_addr(global->mlx_image, &bits_per_pixel, &line_length, &endian);
    if (!dst)
        return;
    dst = dst + (y * line_length + x * (bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

static  float nor_angle(float angle) // normalize the angle
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

void draw_floor_ceiling(t_global *global, int ray, int t_pix, int b_pix) // draw the floor and the ceiling
{
    int  i;
 
	i = b_pix;
	while (i < S_H)
		my_mlx_pixel_put(global, ray, i++, 0x574964); // floor
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(global, ray, i++, 0xC8ACD6); // ceiling
}

int get_color(t_global *global, int flag) // get the color of the wall
{
	global->ray->angle = nor_angle(global->ray->angle); // normalize the angle
	if (flag == 0)
	{
		if (global->ray->angle > M_PI / 2 && global->ray->angle < 3 * (M_PI / 2))
			return (0xC8AAAA); // west wall
		else
			return (0xC8AAAA); // east wall
	}
	else
	{
		if (global->ray->angle > 0 && global->ray->angle < M_PI)
			return (0xF5F5F5FF); // south wall
		else
			return (0xF5F5F5FF); // north wall
	}
}

void draw_wall(t_global *global, int ray, int t_pix, int b_pix) // draw the wall
{
	int color;

	color = get_color(global, global->ray->ray_f);
	while (t_pix < b_pix)
		my_mlx_pixel_put(global, ray, t_pix++, color);
}

void render_wall(int ray) // render the wall
{
    t_global    *global;
	double wall_h;
	double b_pix;
	double t_pix;

    global = *get_heap();
	global->ray->distance *= cos(nor_angle(global->ray->angle - global->player->angle)); // fix the fisheye
	wall_h = (TILE_SIZE / global->ray->distance) * ((S_W / 2) / tan(global->player->fov / 2)); // get the wall height
	b_pix = (S_H / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (S_H / 2) - (wall_h / 2); // get the top pixel
	if (b_pix > S_H) // check the bottom pixel
		b_pix = S_H;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_wall(global, ray, t_pix, b_pix); // draw the wall
	draw_floor_ceiling(global, ray, t_pix, b_pix); // draw the floor and the ceiling
	
}
