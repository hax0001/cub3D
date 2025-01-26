/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:54:06 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/26 01:28:43 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"


void draw_player(t_global *global)
{
    void *img_player;
    int player_width, player_height;
    char *player_data;
    int bits_per_pixel, line_length, endian;

    // Load the player image from the .xpm file
    img_player = mlx_xpm_file_to_image(global->mlx_p, "textures/player/fps_gun.xpm", &player_width, &player_height);
    if (!img_player)
    {
        // Handle error if image loading fails
        return;
    }

    // Access the pixel data address of the loaded image
    player_data = mlx_get_data_addr(img_player, &bits_per_pixel, &line_length, &endian);
    
    // Clear the image buffer (fill it with black or a background color)
    ft_memset(mlx_get_data_addr(global->mlx_image, &(int){0}, &(int){0}, &(int){0}), 0, S_W * S_H * 4);

    // Calculate the position to place the player image at the bottom middle
    int player_x = (S_W - player_width) / 2; // Center horizontally
    int player_y = S_H - player_height;      // Place at the bottom

    // Put the image to the window at the calculated position
    mlx_put_image_to_window(global->mlx_p, global->mlx_w, img_player, player_x, player_y);

    // Optionally destroy the image if not needed anymore
    // mlx_destroy_image(global->mlx_p, img_player);
}



void    ft_exit(void)
{
    t_global    *global;

    global = *get_heap();
    mlx_destroy_window(global->mlx_p,  global->mlx_w);   
    mlx_destroy_image(global->mlx_p,  global->mlx_image);
    mlx_destroy_display(global->mlx_p);
    ft_free_all();
    exit(1);
    // free(global);
}

int play(void *info)
{
    t_global *global;
    
    int flg = 1;
    global = (t_global *)info;
    if (!global || !global->mlx_image)
        return (1);
    ft_memset(mlx_get_data_addr(global->mlx_image, &(int){0}, &(int){0}, &(int){0}), 0, S_W * S_H * 4);
    cast_rays();
    
    draw_minimap(global);
    mouve(global ,0 ,0);
    // draw_player(global);
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
    player->angle = global->data->angle;
    player->fov = FOV * (M_PI / 180);
}


void cub3d(void)
{
    t_global *global;
    
    global = *get_heap();
    global->player = (t_player *)ft_malloc(sizeof(t_player));
    ft_memset(global->player, 0, sizeof(t_player));
    global->ray = (t_ray *)ft_malloc(sizeof(t_ray));
    ft_memset(global->ray, 0, sizeof(t_ray));
    
    global->mlx_p = mlx_init();
    if (!global->mlx_p)
        ft_error(ERR_MLX_INIT_FAILED);
    global->mlx_w = mlx_new_window(global->mlx_p, S_W, S_H, "cub3d");
    if (!global->mlx_w)
        ft_error(ERR_MLX_INIT_FAILED);
    global->mlx_image = mlx_new_image(global->mlx_p, S_W, S_H);
    if (!global->mlx_image)
        ft_error(ERR_MLX_INIT_FAILED);
    init_player();
    load_textures(global); // take
    mlx_hook(global->mlx_w, 2, 1L<<0, key_press, global); 
    mlx_hook(global->mlx_w, 3, 1L<<1, key_release, global);  
    mlx_hook(global->mlx_w, 17, 0, (void *)ft_exit, NULL);   
    mlx_loop_hook(global->mlx_p, play, global);
    mlx_loop(global->mlx_p);
}
