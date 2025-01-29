/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:46:36 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/29 01:31:57 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

float	nor_angle(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

int	unit_circle(float angle, char axis)
{
	if (axis == 'x')
		return (angle > 0 && angle < M_PI);
	return (angle > M_PI / 2 && angle < 3 * M_PI / 2);
}

void	draw_floor_ceiling(t_global *global, int ray, int t_pix, int b_pix)
{
	int	i;

	i = b_pix;
	while (i < S_H)
		my_mlx_pixel_put(global, ray, i++, global->data->c_color);
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(global, ray, i++, global->data->f_color);
}

void	ft_exit(void)
{
	t_global	*global;

	global = *get_heap();
	mlx_destroy_image(global->mlx_p, global->data->north_tex->img);
	mlx_destroy_image(global->mlx_p, global->data->south_tex->img);
	mlx_destroy_image(global->mlx_p, global->data->east_tex->img);
	mlx_destroy_image(global->mlx_p, global->data->west_tex->img);
	mlx_destroy_window(global->mlx_p, global->mlx_w);
	mlx_destroy_image(global->mlx_p, global->mlx_image);
	mlx_destroy_display(global->mlx_p);
	free(global->mlx_p);
	ft_free_all();
	exit(1);
}

void	norm(t_global *global, double x)
{
	global->ray->ray_f = 1;
	global->ray->distance = x;
}
