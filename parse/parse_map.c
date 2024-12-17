/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:26:26 by nait-bou          #+#    #+#             */
/*   Updated: 2024/12/16 14:16:07 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

t_data  *parse_map()
{
    t_data  *data;

    data = (t_data *)ft_malloc(sizeof(t_data));  // u shoud alocate memory for data in ur new parsing version
    data->map = (char **)ft_malloc(sizeof(char *) * 10);
    data->map[0] = ft_strdup("1111111111111111111111111");
    data->map[1] = ft_strdup("1000000000000000000100001");
    data->map[2] = ft_strdup("1001000000000P00000000001");
    data->map[3] = ft_strdup("1001000000000000001000001");
    data->map[4] = ft_strdup("1001000000000000001000001");
    data->map[5] = ft_strdup("1001000000100000001000001");
    data->map[6] = ft_strdup("1001000000000000001000001");
    data->map[7] = ft_strdup("1001000000001000001000001");
    data->map[8] = ft_strdup("1000000000000000000000001");
    data->map[9] = ft_strdup("1111111111111111111111111");
    data->map[10] = NULL;
    data->y_p_m = 3;
    data->x_p_m = 14;
    data->w_map = 25;
    data->h_map = 9;
    return (data);
}