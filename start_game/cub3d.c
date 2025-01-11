/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:54:06 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/11 17:18:57 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"



void    ft_exit(void)
{
    //t_global    *global;

    //global = *get_heap();
   // mlx_destroy_window(global->mlx_p,  global->mlx_w);
    exit(0);
}

int    play(void *info)
{
    t_global    *global;
    
    global = (t_global *)info;
    //printf("cub3d\n");
    //mlx_destroy_image(global->mlx_p, global->mlx_image);
    global->mlx_image = mlx_new_image(global->mlx_p, S_W, S_H);
    mlx_put_image_to_window(global->mlx_p, global->mlx_w, global->mlx_image, 0, 0);
    return (0);
}

void    init_player(void)
{
    t_global    *global;
    t_player    *player;
    
    global = *get_heap();
    player = global->player;
    player->x_p = global->data->x_p_m * TILE_SIZE + TILE_SIZE / 2;
    player->y_p = global->data->y_p_m * TILE_SIZE + TILE_SIZE / 2;
    player->angle = M_PI;
    player->fov = FOV * (M_PI / 180);
}

void    cub3d(void)
{
    t_global   *global;
    
    global = *get_heap();
    global->player = (t_player *)ft_malloc(sizeof(t_player));
    ft_memset(global->player, 0, sizeof(t_player));
    global->ray = (t_ray *)ft_malloc(sizeof(t_ray));
    ft_memset(global->ray, 0, sizeof(t_ray));
    //global->mlx_p = mlx_init();
    //if(!global->mlx_p)
       // ft_error(ERR_MLX_INIT_FAILED);
    //global->mlx_w = mlx_new_window(global->mlx_p, S_W, S_H, "cub3d");
    //if(!global->mlx_w)
        //ft_error(ERR_MLX_INIT_FAILED);
    init_player();
   // mlx_loop_hook(global->mlx_p, play, global);
    //mlx_loop(global->mlx_p);
    cast_rays();
    ft_exit();

}