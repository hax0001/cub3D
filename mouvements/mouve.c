/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:18:15 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/20 17:11:20 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void mouve_player(t_global *global, double move_x, double move_y)
{
    int map_y;
    int map_x;
    int new_x;
    int new_y;
    
    new_x = roundf(global->player->x_p + move_x);
    new_y = roundf(global->player->y_p + move_y);
    map_x = (new_x / TILE_SIZE);
    map_y = (new_y / TILE_SIZE);
    if (map_y < 0 || map_y >= global->data->h_map || 
        map_x < 0 || map_x >= global->data->w_map)
        return;    
    if (global->data->map[map_y] && 
        map_x < (int)ft_strlen(global->data->map[map_y]) &&
        global->data->map[map_y][map_x] != '1')
    {
        global->player->x_p = new_x;
        global->player->y_p = new_y;
    }
}


void	rotate_player(t_global *global, int i)
{
	if (i == 1)
	{
		global->player->angle += R_SPEED;
		if (global->player->angle > 2 * M_PI)
			global->player->angle -= 2 * M_PI;
	}
	else
	{
		global->player->angle -= R_SPEED;
		if (global->player->angle < 0)
			global->player->angle += 2 * M_PI;
	}
}

void mouve(t_global *global, double move_x, double move_y)
{
    if (global->player->u_d == 1)
    {
        move_x = cos(global->player->angle) * P_SPEED;
        move_y = sin(global->player->angle) * P_SPEED;
    }
    else if (global->player->u_d == -1)
    {
        move_x = -cos(global->player->angle) * P_SPEED;
        move_y = -sin(global->player->angle) * P_SPEED;
    }
    if (global->player->l_r == 1)
    {
        move_x -= sin(global->player->angle) * P_SPEED;
        move_y += cos(global->player->angle) * P_SPEED;
    }
    else if (global->player->l_r == -1)
    {
        move_x += sin(global->player->angle) * P_SPEED;
        move_y -= cos(global->player->angle) * P_SPEED;
    }
    if (global->player->r_f == 1)
        rotate_player(global, 1);
    else if (global->player->r_f == -1)
        rotate_player(global, 0);
    mouve_player(global, move_x, move_y);
}

int key_press(int keycode, void *info)
{
    t_global *global;
    
    global = (t_global *)info;
    if (keycode == 65307) 
        ft_exit();
    else if (keycode == 97)  
        global->player->l_r = -1;
    else if (keycode == 100) 
        global->player->l_r = 1;
    else if (keycode == 115) 
        global->player->u_d = -1;
    else if (keycode == 119) 
        global->player->u_d = 1;
    else if (keycode == 65361) 
        global->player->r_f = -1;
    else if (keycode == 65363) 
        global->player->r_f = 1;
    return (0);
}

int key_release(int keycode, void *info)
{
    t_global *global;
    
    global = (t_global *)info;
    if (keycode == 97 || keycode == 100) // A or D
        global->player->l_r = 0;
    else if (keycode == 115 || keycode == 119) // S or W
        global->player->u_d = 0;
    else if (keycode == 65361 || keycode == 65363) // Left or Right arrow
        global->player->r_f = 0;
    return (0);
}
