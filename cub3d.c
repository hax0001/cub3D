/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:23:38 by nait-bou          #+#    #+#             */
/*   Updated: 2024/12/14 18:16:37 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/cub3d.h"

t_global   *g_global;

int main(int ac, char **av)
{
    t_global   *global;

    (void)av;
    global = (t_global *)ft_malloc(sizeof(t_global));
    g_global = global;
    if (ac != 2)
    {
        write(1, "Error\n", 6);
        write(1, "Usage: ./cub3d <map.cub>\n", 25);
        return (0);
    }


    return (0);
}