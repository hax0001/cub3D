/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:46:36 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/28 01:12:48 by akajjou          ###   ########.fr       */
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

void	ft_cast_ray(t_global *global, int horiz_dist)
{
	global->ray->ray_f = 1;
	global->ray->distance = horiz_dist;
}
