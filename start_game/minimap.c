/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:55:44 by akajjou           #+#    #+#             */
/*   Updated: 2025/01/27 19:15:41 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void draw_minimap_pixel(t_global *global, int x, int y, int color)
{
    char *dst;
    int bits_per_pixel;
    int line_length;
    int endian;
    int screen_x;
    int screen_y;

    screen_x = x + MINIMAP_PADDING;
    screen_y = y + MINIMAP_PADDING;

    if (screen_x < MINIMAP_PADDING || screen_x >= MINIMAP_SIZE + MINIMAP_PADDING || 
        screen_y < MINIMAP_PADDING || screen_y >= MINIMAP_SIZE + MINIMAP_PADDING)
        return;

    dst = mlx_get_data_addr(global->mlx_image, &bits_per_pixel, &line_length, &endian);
    dst = dst + (screen_y * line_length + screen_x * (bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void draw_minimap_rect(t_global *global, int x, int y, int color)
{
    int size;
    int i;
    int j;

    size = TILE_SIZE * MINIMAP_SCALE;
    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            draw_minimap_pixel(global, x * size + i, y * size + j, color);
            j++;
        }
        i++;
    }
}

void draw_minimap_player(t_global *global)
{
    int player_x;
    int player_y;
    int player_size;
    int i;
    int j;

    player_x = global->player->x_p * MINIMAP_SCALE;
    player_y = global->player->y_p * MINIMAP_SCALE;
    player_size = 5;
    i = -player_size;
    while (i < player_size)
    {
        j = -player_size;
        while (j < player_size)
        {
            if (i * i + j * j <= player_size * player_size)
                draw_minimap_pixel(global, player_x + i, player_y + j, 0xED4C67);
            j++;
        }
        i++;
    }
}


void draw_minimap(t_global *global)
{
    int x;
    int y;

    y = 0;
    while (y < global->data->h_map)
    {
        x = 0;
        while (x < global->data->w_map)
        {
            if (global->data->map[y] && x < (int)ft_strlen(global->data->map[y]))
            {
                if (global->data->map[y][x] == '1')
                    draw_minimap_rect(global, x, y, 0x0652DD);
                else if (global->data->map[y][x] == '0' || player_char(global->data->map[y][x]))
                    draw_minimap_rect(global, x, y, 0x9980FA);
            }
            x++;
        }
        y++;
    }
    draw_minimap_player(global);
}
