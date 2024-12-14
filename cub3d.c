/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:23:38 by nait-bou          #+#    #+#             */
/*   Updated: 2024/12/13 14:30:07 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/cub3d.h"

int main(int ac, char **av)
{
    t_mlx   *mlx;
    t_data  *data;
    t_player    *player;
    t_ray   *ray;

    mlx = get_heap();
    if (ac != 2)
    {
        write(1, "Error\n", 6);
        write(1, "Usage: ./cub3d <map.cub>\n", 25);
        return (0);
    }
    mlx = ft_malloc(sizeof(t_mlx));
    data = ft_malloc(sizeof(t_data));
    player = ft_malloc(sizeof(t_player));
    ray = ft_malloc(sizeof(t_ray));

    return (0);
}