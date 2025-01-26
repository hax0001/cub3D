/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:23:38 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/26 22:11:59 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/cub3d.h"

void print_data(t_data *data)
{
    if (data != NULL)
    {
        printf("NO: %s\n", data->no);
        printf("SO: %s\n", data->so);
        printf("WE: %s\n", data->we);
        printf("EA: %s\n", data->ea);
        printf("F: %u\n", data->f_color);
        printf("C: %u\n", data->c_color);
        printf("player_X = %d\n",data->x_p_m);
        printf("player_y = %d\n",data->y_p_m);
        printf("map_W = %d\n",data->w_map);
        printf("map_H = %d\n",data->h_map);
        int i = 0;
        printf("<------------MAP--------->\n");
        while (data->map[i])
        {
            printf("%s\n", data->map[i++]);
        }
    }
    else
    {
        printf("Data is NULL.\n");
    }
}

int main(int ac, char **av)
{
    t_global *global;

    *get_heap() = NULL;
    if (filename_check(ac, av) == false)
        return (2);
    global = (t_global *)ft_malloc(sizeof(t_global)); // Allocate memory for global
    ft_memset(global, 0, sizeof(t_global));
    global->gar_co = NULL; // Initialize gar_co
    *get_heap() = global;
    if (parses_map(&global, global->data, av[1]) == false)
        return (ft_free_all(), 2);
    cub3d();
    ft_free_all(); // Free all allocated memory
    return (0);
}