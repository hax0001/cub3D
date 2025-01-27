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
    int line_length;
    int end_x;
    int end_y;
    double dx;
    double dy;
    double steps;
    double x;
    double y;

    player_x = global->player->x_p * MINIMAP_SCALE;
    player_y = global->player->y_p * MINIMAP_SCALE;
    player_size = 4;
    i = -player_size;
    while (i < player_size)
    {
        j = -player_size;
        while (j < player_size)
        {
            if (i * i + j * j <= player_size * player_size)
                draw_minimap_pixel(global, player_x + i, player_y + j, 0xFF0000);
            j++;
        }
        i++;
    }

    line_length = 10;
    end_x = player_x + cos(global->player->angle) * line_length;
    end_y = player_y + sin(global->player->angle) * line_length;
    dx = end_x - player_x;
    dy = end_y - player_y;
    steps = fmax(fabs(dx), fabs(dy));
    if (steps == 0)
        return;
    dx /= steps;
    dy /= steps;
    x = player_x;
    y = player_y;
    i = 0;
    while (i <= steps)
    {
        draw_minimap_pixel(global, round(x), round(y), 0xFFFF00);
        x += dx;
        y += dy;
        i++;
    }
}

void draw_minimap_background(t_global *global)
{
    int size;
    int i;
    int j;
    char *dst;

    size = MINIMAP_SIZE + (MINIMAP_PADDING * 2);
    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            if (i < MINIMAP_PADDING || i >= size - MINIMAP_PADDING ||
                j < MINIMAP_PADDING || j >= size - MINIMAP_PADDING)
            {
                j++;
                continue;
            }
            dst = mlx_get_data_addr(global->mlx_image, &(int){0}, &(int){0}, &(int){0});
            dst = dst + (j * S_W * 4 + i * 4);
            *(unsigned int *)dst = 0x80000000;
            j++;
        }
        i++;
    }
}

void draw_minimap(t_global *global)
{
    int x;
    int y;

    draw_minimap_background(global);

    y = 0;
    while (y < global->data->h_map)
    {
        x = 0;
        while (x < global->data->w_map)
        {
            if (global->data->map[y] && x < (int)ft_strlen(global->data->map[y]))
            {
                if (global->data->map[y][x] == '1')
                    draw_minimap_rect(global, x, y, 0x808080);
                else if (global->data->map[y][x] == '0')
                    draw_minimap_rect(global, x, y, 0x404040);
            }
            x++;
        }
        y++;
    }

    draw_minimap_player(global);
}
