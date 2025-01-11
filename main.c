/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:23:38 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/11 21:30:27 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/cub3d.h"


bool    FileName_check( int argc, char **argv)
{
    int     FileLen;
    char    *FileName;
    
    if (argc != 2)
    {
        printf("Error\nUsage : ./cub3d <map>\n");
        return false;
    }
    FileLen = strlen(argv[1]) - 4;
    FileName = argv[1];
    if (strcmp( FileName + FileLen, ".cub") != 0)
    {   
        printf("Error\nBad extension\n");
        return false;
    }   
    return true;
}

bool    parse_map( void )
{
    t_global *global;

    global = *get_heap();
    global->data->map    
}


int main(int ac, char **av)
{
    t_global   *global;

    if (FileName_check( ac, av) == false)
        return (2);
    global = (t_global *)malloc(sizeof(t_global)); // this memory shoud freed manually with free function
    ft_memset(global, 0, sizeof(t_global));
    *get_heap() = global;
    if (parse_map() == false)
        return (2);
    // cub3d();
    
    return (0);
}