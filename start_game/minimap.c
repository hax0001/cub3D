/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:55:44 by akajjou           #+#    #+#             */
/*   Updated: 2025/01/29 01:02:52 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	draw_minimap_rect(t_global *global, int x, int y, int color)
{
	int	size;
	int	i;
	int	j;

	size = TILE_SIZE * MINIMAP_SCALE;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(global, x * size + i, y * size + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_player(t_global *global)
{
	int	player_x;
	int	player_y;
	int	player_size;
	int	i;
	int	j;

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
				my_mlx_pixel_put(global, player_x + i, player_y + j, 0xED4C67);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_global *global)
{
	int	x;
	int	y;

	y = 0;
	while (y < global->data->h_map)
	{
		x = 0;
		while (x < global->data->w_map)
		{
			if (global->data->map[y]
				&& x < (int)ft_strlen(global->data->map[y]))
			{
				if (global->data->map[y][x] == '1')
					draw_minimap_rect(global, x, y, 0x0652DD);
				else if (global->data->map[y][x] == '0'
						|| player_char(global->data->map[y][x]))
					draw_minimap_rect(global, x, y, 0x9980FA);
			}
			x++;
		}
		y++;
	}
	draw_minimap_player(global);
}
