/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:23:38 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/18 17:31:18 by akajjou          ###   ########.fr       */
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
    t_global   *global;

    if (FileName_check( ac, av) == false)
        return (2);
    global = (t_global *)malloc(sizeof(t_global)); // this memory shoud freed manually with free function
    ft_memset(global, 0, sizeof(t_global));
    *get_heap() = global;
    if (parses_map(global->data, av[1]) == false)
        return (2);
    // cub3d();
    
    return (0);
}