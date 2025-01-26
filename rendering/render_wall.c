/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:03:25 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/26 23:09:26 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

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

// static  float nor_angle(float angle)
// {
// 	if (angle < 0)
// 		angle += (2 * M_PI);
// 	if (angle > (2 * M_PI))
// 		angle -= (2 * M_PI);
// 	return (angle);
// }

void draw_floor_ceiling(t_global *global, int ray, int t_pix, int b_pix)
{
    int  i;
 
	i = b_pix;
	while (i < S_H)
		my_mlx_pixel_put(global, ray, i++, global->data->f_color);
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(global, ray, i++, global->data->c_color);
}

t_texture  *get_texture_index(t_global *global)
{
    if (global->ray->ray_f == 0)
    {
        if (global->ray->angle > M_PI && global->ray->angle < 2 * M_PI)
            return global->data->south_tex;
        else
            return global->data->north_tex;
    }
    else 
    {
        if (global->ray->angle > M_PI / 2 && global->ray->angle < 3 * M_PI / 2)
            return global->data->west_tex;
        else
            return global->data->east_tex;
    }
}


void draw_wall(t_global *global, int ray, int t_pix, int b_pix ,int wall_h) 
{

	int y;
	int d;
    char *texture_data;
    int tex_x, tex_y;
    int wall_x;
    t_texture *img;


	y = t_pix;
    img = get_texture_index(global);
    texture_data = img->addr;

    if (global->ray->ray_f == 1) // Horizontal wall
    	wall_x = (int)global->ray->horiz_x % TILE_SIZE;
	else // Vertical wall
    	wall_x = (int)global->ray->vert_y % TILE_SIZE; 

	tex_x = (int)(wall_x * img->width) / TILE_SIZE;

	while (y < b_pix)
	{
        d = y + (wall_h / 2) -  S_H / 2;
        tex_y = (d * img->height + wall_h / 2) / wall_h;
        tex_y = tex_y % img->height;
        int *addr = (int *)texture_data;
        int color = addr[tex_y * img->width + tex_x];
        my_mlx_pixel_put(global, ray, y, color);
	    y++;
	}
}

void render_wall(int ray) 
{
    t_global *global;
    double wall_h, t_pix, b_pix;

    global = *get_heap();

    global->ray->distance *= cos(global->ray->angle - global->player->angle);

    wall_h = (TILE_SIZE / global->ray->distance) * ((S_W / 2) / tan(global->player->fov / 2));
    b_pix = (S_H / 2) + (wall_h / 2);
    t_pix = (S_H / 2) - (wall_h / 2);
    if (b_pix > S_H)
        b_pix = S_H;
    if (t_pix < 0)
        t_pix = 0;
    
    draw_wall(global, ray, t_pix, b_pix, wall_h);
    draw_floor_ceiling(global, ray, t_pix, b_pix); 
}


