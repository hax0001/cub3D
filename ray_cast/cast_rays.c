/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:46:36 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/13 14:13:54 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"


float nor_angle(float angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle >= 2 * M_PI)
        angle -= 2 * M_PI;
    return angle;
}


// Check which quadrant of unit circle the angle is in
int unit_circle(float angle, char axis)
{
    if (axis == 'x')
        return (angle > 0 && angle < M_PI);
    return (angle > M_PI / 2 && angle < 3 * M_PI / 2);
}

// Calculate intersection step and direction
int calculate_intersection(
    float angle, float *intersection, float *step, int is_horizontal)
{
    if (is_horizontal)
    {
        if (angle > 0 && angle < M_PI)
        {
            *intersection += TILE_SIZE;
            return (-1);
        }
        *step *= -1;
    }
    else
    {
        if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
        {
            *intersection += TILE_SIZE;
            return (-1);
        }
        *step *= -1;
    }
    return (1);
}

// Check if ray hit a wall
int wall_hit(float x, float y, t_global *global)
{
    int map_x;
    int map_y;

    if (x < 0 || y < 0)
        return (0);
    map_x = floor(x / TILE_SIZE);
    map_y = floor(y / TILE_SIZE);
    if (map_y >= global->data->h_map || map_x >= global->data->w_map)
        return (0);
    if (global->data->map[map_y] && map_x <= (int)ft_strlen(global->data->map[map_y]))
        if (global->data->map[map_y][map_x] == '1')
            return (0);
    return (1);
}

// Calculate horizontal intersections
float get_horizontal_intersection(t_global *global, float angle)
{
    float horiz_x;
    float horiz_y;
    float x_step;
    float y_step;
    int pixel;

    x_step = TILE_SIZE / tan(angle);
    y_step = TILE_SIZE;
    horiz_y = floor(global->player->y_p / TILE_SIZE) * TILE_SIZE;
    pixel = calculate_intersection(angle, &horiz_y, &y_step, 1);
    horiz_x = global->player->x_p + (horiz_y - global->player->y_p) / tan(angle);
    if ((unit_circle(angle, 'y') && x_step > 0) ||
        (!unit_circle(angle, 'y') && x_step < 0))
        x_step *= -1;
    while (wall_hit(horiz_x, horiz_y - pixel, global))
    {
        horiz_x += x_step;
        horiz_y += y_step;
    }
    return (sqrt(pow(horiz_x - global->player->x_p, 2) +
                 pow(horiz_y - global->player->y_p, 2)));
}

// Calculate vertical intersections
float get_vertical_intersection(t_global *global, float angle)
{
    float vert_x;
    float vert_y;
    float x_step;
    float y_step;
    int pixel;

    x_step = TILE_SIZE;
    y_step = TILE_SIZE * tan(angle);
    vert_x = floor(global->player->x_p / TILE_SIZE) * TILE_SIZE;
    pixel = calculate_intersection(angle, &vert_x, &x_step, 0);
    vert_y = global->player->y_p + (vert_x - global->player->x_p) * tan(angle);
    if ((unit_circle(angle, 'x') && y_step < 0) ||
        (!unit_circle(angle, 'x') && y_step > 0))
        y_step *= -1;
    while (wall_hit(vert_x - pixel, vert_y, global))
    {
        vert_x += x_step;
        vert_y += y_step;
    }
    return (sqrt(pow(vert_x - global->player->x_p, 2) +
                 pow(vert_y - global->player->y_p, 2)));
}

// Main raycasting function
void cast_rays()
{
    t_global    *global;
    double horiz_dist;
    double vert_dist;
    float current_angle;
    int ray;

    global = *get_heap();
    global->ray->angle = global->player->angle - (global->player->fov / 2);
    ray = 0;
    while (ray < S_W)
    {
        global->ray->ray_f = 0;
        current_angle = nor_angle(global->ray->angle);
        
        // Get both distances
        horiz_dist = get_horizontal_intersection(global, current_angle);
        vert_dist = get_vertical_intersection(global, current_angle);
        
        // Choose shorter distance
        if (vert_dist <= horiz_dist)
            global->ray->distance = vert_dist;
        else
        {
            global->ray->ray_f = 1;
            global->ray->distance = horiz_dist;
        }
        render_wall(ray);
        global->ray->angle += global->player->fov / S_W;
        ray++;
    }
}

//           +++++ the rest of code is just to visualize 

// void draw_pixel(int x, int y, int color)
// {
//     t_global *global;
//     char    *dst;
//     int     bits_per_pixel;
//     int     line_length;
//     int     endian;

//     global = *get_heap();
//     dst = mlx_get_data_addr(global->mlx_image, &bits_per_pixel, &line_length, &endian);
//     if (x >= 0 && x < S_W && y >= 0 && y < S_H)
//     {
//         dst = dst + (y * line_length + x * (bits_per_pixel / 8));
//         *(unsigned int*)dst = color;
//     }
// }

// void draw_rectangle(int x, int y, int color)
// {
//     int i;
//     int j;

//     i = 0;
//     while (i < TILE_SIZE)
//     {
//         j = 0;
//         while (j < TILE_SIZE)
//         {
//             draw_pixel(x + i, y + j, color);
//             j++;
//         }
//         i++;
//     }
// }



// void draw_line(int x1, int y1, int x2, int y2, int color)
// {
//     double dx = x2 - x1;
//     double dy = y2 - y1;
//     double step = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
//     double x_inc = dx / step;
//     double y_inc = dy / step;
//     double x = x1;
//     double y = y1;
//     int i = 0;

//     while (i <= step)
//     {
//         draw_pixel(round(x), round(y), color);
//         x += x_inc;
//         y += y_inc;
//         i++;
//     }
// }

// void draw_player(t_global *global)
// {
//     int player_size = 8;
//     int x = global->player->x_p;
//     int y = global->player->y_p;
//     int i;
//     int j;

//     // Draw player circle
//     i = -player_size;
//     while (i < player_size)
//     {
//         j = -player_size;
//         while (j < player_size)
//         {
//             if (i * i + j * j <= player_size * player_size)
//                 draw_pixel(x + i, y + j,COLOR_RED);
//             j++;
//         }
//         i++;
//     }

//     // Draw direction line
//     int line_length = 20;
//     int end_x = x + cos(global->player->angle) * line_length;
//     int end_y = y + sin(global->player->angle) * line_length;
//     draw_line(x, y, end_x, end_y,COLOR_YELLOW);
// }

// void draw_map(void)
// {
//     t_global *global;
//     int x;
//     int y;

//     global = *get_heap();
    
//     // Draw map grid
//     y = 0;
//     while (global->data->map[y])
//     {
//         x = 0;
//         while (global->data->map[y][x])
//         {
//             if (global->data->map[y][x] == '1')
//                 draw_rectangle(x * TILE_SIZE, y * TILE_SIZE,COLOR_BLUE);
//             x++;
//         }
//         y++;
//     }

//     // Draw player
//     draw_player(global);

//     // Draw FOV rays
//     float ray_angle = global->player->angle - (global->player->fov / 2);
//     int i = 0;
//     while (i < S_W)
//     {
//         ray_angle = nor_angle(ray_angle);
//         int ray_x = global->player->x_p + cos(ray_angle) * global->ray->distance;
//         int ray_y = global->player->y_p + sin(ray_angle) * global->ray->distance;
//         draw_line(global->player->x_p, global->player->y_p, ray_x, ray_y,COLOR_GREEN);
//         ray_angle += global->player->fov / S_W;
//         i++;
//     }
// }


