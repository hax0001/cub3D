/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:03:25 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/23 00:28:57 by akajjou          ###   ########.fr       */
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

// hna
void	load_texture(t_global *global, t_texture **tex, char *path)
{
	*tex = ft_malloc(sizeof(t_texture));
	(*tex)->img = mlx_xpm_file_to_image(global->mlx_p, path,
			&(*tex)->width + 1, &(*tex)->height);
	if (!(*tex)->img)
		ft_error("Failed to load texture");
	(*tex)->addr = mlx_get_data_addr((*tex)->img, &(*tex)->bits_per_pixel,
			&(*tex)->line_length, &(*tex)->endian);
}

char	*ft_path_to_texture(char *str)
{
	char	**texture;
	char	*ret_texture;

	texture = ft_split(str, ' ');
	ret_texture = ft_strdup(texture[1]);
	return (ret_texture);
}

void	init_textures(t_global *global)
{
	load_texture(global, &global->data->north_tex,
		ft_path_to_texture(global->data->no));
	load_texture(global, &global->data->south_tex,
		ft_path_to_texture(global->data->so));
	load_texture(global, &global->data->east_tex,
		ft_path_to_texture(global->data->ea));
	load_texture(global, &global->data->west_tex,
		ft_path_to_texture(global->data->we));
}

static void	clamp_coordinates(int *x, int *y, t_texture *tex)
{
	if (*x >= tex->width)
		*x = tex->width - 1;
	if (*y >= tex->height)
		*y = tex->height - 1;
	if (*x < 0)
		*x = 0;
	if (*y < 0)
		*y = 0;
}

unsigned int	get_texture_color(t_texture *tex, int x, int y)
{
	char	*dst;

	clamp_coordinates(&x, &y, tex);
	dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

t_texture	*get_wall_texture_horizontal(t_global *global, float angle)
{
	if (angle > 0 && angle < M_PI)
		return (global->data->south_tex);
	return (global->data->north_tex);
}

t_texture	*get_wall_texture_vertical(t_global *global, float angle)
{
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		return (global->data->west_tex);
	return (global->data->east_tex);
}

t_texture	*get_wall_texture(t_global *global)
{
	float	angle;

	angle = nor_angle(global->ray->angle);
	if (global->ray->ray_f)
		return (get_wall_texture_horizontal(global, angle));
	return (get_wall_texture_vertical(global, angle));
}

static double	calculate_wall_x(t_global *global)
{
	double	wall_x;

	if (global->ray->ray_f)  // Horizontal hit
	{
		wall_x = global->player->x_p + global->ray->distance
			* cos(global->ray->angle);
	}
	else  // Vertical hit
	{
		wall_x = global->player->y_p + global->ray->distance
			* sin(global->ray->angle);
	}
	wall_x = wall_x - floor(wall_x);
	if (wall_x < 0)
		wall_x = 1 + wall_x;
	return (wall_x);
}


static int	calculate_tex_x(t_global *global, double wall_x, int tex_width)
{
	int	tex_x;

	// Convert wall_x to texture coordinate
	tex_x = (int)(wall_x * (double)tex_width);
	
	// Flip texture if needed based on wall orientation
	if ((!global->ray->ray_f && global->ray->angle > M_PI / 2
			&& global->ray->angle < 3 * M_PI / 2)
		|| (global->ray->ray_f && !(global->ray->angle > 0
			&& global->ray->angle < M_PI)))
		tex_x = tex_width - tex_x - 1;

	// Ensure texture x-coordinate stays within bounds
	tex_x = tex_x % tex_width;
	if (tex_x < 0)
		tex_x = 0;
		
	return (tex_x);
}


static void	draw_wall_strip(t_global *global, int ray, int t_pix,
	t_draw_info *info)
{
	int				y;
	int				tex_y;
	double			tex_pos;
	double			step;
	unsigned int	color;

	// Calculate step based on actual wall height
	step = (double)info->tex->height / (double)(info->b_pix - t_pix);
	tex_pos = 0;
	y = t_pix;
	while (y < info->b_pix)
	{
		// Ensure texture y-coordinate stays within bounds
		tex_y = (int)tex_pos % info->tex->height;
		if (tex_y < 0)
			tex_y = 0;
		color = get_texture_color(info->tex, info->tex_x, tex_y);
		my_mlx_pixel_put(global, ray, y, color);
		tex_pos += step;
		y++;
	}
}

void	draw_textured_wall(t_global *global, int ray, int t_pix, int b_pix)
{
	t_texture	*tex;
	t_draw_info	info;
	double		wall_x;

	// Get the correct texture based on wall orientation
	tex = get_wall_texture(global);
	info.tex = tex;
	info.b_pix = b_pix;

	// Calculate texture coordinates
	wall_x = calculate_wall_x(global);
	info.tex_x = calculate_tex_x(global, wall_x, tex->width);

	// Draw the wall strip with proper scaling
	draw_wall_strip(global, ray, t_pix, &info);
}

// hna

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
	// draw_wall(global, ray, t_pix, b_pix); // draw the wall
	draw_textured_wall(global, ray, t_pix, b_pix);
	draw_floor_ceiling(global, ray, t_pix, b_pix); // draw the floor and the ceiling
	
}
