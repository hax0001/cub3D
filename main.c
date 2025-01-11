/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:23:38 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/11 22:40:07 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/cub3d.h"



int main(int ac, char **av)
{
    t_global   *global;

    if (FileName_check( ac, av) == false)
        return (2);
    global = (t_global *)malloc(sizeof(t_global)); // this memory shoud freed manually with free function
    ft_memset(global, 0, sizeof(t_global));
    *get_heap() = global;
    if (parses_map(av[1]) == false)
        return (2);
    // cub3d();
    
    return (0);
}