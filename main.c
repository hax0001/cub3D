/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:23:38 by nait-bou          #+#    #+#             */
/*   Updated: 2024/12/17 13:17:29 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/cub3d.h"

int main(int ac, char **av)
{
    t_global   *global;

    (void)av;
    (void)ac;
    global = (t_global *)ft_malloc(sizeof(t_global));
    ft_memset(global, 0, sizeof(t_global));
    *get_heap() = global;
    // u shoud parse the argument here {files.cub}
    global->data = parse_map();
    cub3d();
    
    return (0);
}