/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:18:01 by akajjou           #+#    #+#             */
/*   Updated: 2025/01/21 13:24:15 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

bool	player_char(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (true);
	return (false);
}

bool	map_border_updown(char **map)
{
	int		v_index;
	size_t	c_index;

	v_index = 1;
	while (map[v_index] && v_index != ft_arg_count(map))
	{
		c_index = 0;
		while (map[v_index][c_index])
		{
			if (map[v_index][c_index] == '0'
				|| player_char(map[v_index][c_index]))
			{
				if (c_index >= ft_strlen(map[v_index + 1])
					|| c_index >= ft_strlen(map[v_index - 1]))
					return (printf("Error\nThe Map Is Invalid\n"), false);
				if (map[v_index + 1][c_index] == ' ' || map[v_index
					- 1][c_index] == ' ')
					return (printf("Error\nThe Map Is Invalid\n"), false);
			}
			c_index++;
		}
		v_index++;
	}
	return (true);
}

void	player_view(t_data *data, char **map)
{
	int	v_index;
	int	c_index;

	v_index = 1;
	while (map[v_index])
	{
		c_index = 0;
		while (map[v_index][c_index])
		{
			if (player_char(map[v_index][c_index]) == true)
			{
				if (map[v_index][c_index] == 'N')
					data->angle = M_PI / 2;
				if (map[v_index][c_index] == 'S')
					data->angle = (3 * M_PI) / 2;
				if (map[v_index][c_index] == 'W')
					data->angle = 2 * M_PI;
				if (map[v_index][c_index] == 'E')
					data->angle = 0;
				return ;
			}
			c_index++;
		}
		v_index++;
	}
}

bool	map_valid_char(char **map)
{
	int	v_index;
	int	c_index;
	int	player;

	player = 0;
	v_index = 1;
	while (map[v_index])
	{
		c_index = 0;
		while (map[v_index][c_index])
		{
			if (player_char(map[v_index][c_index]) == true)
				player++;
			c_index++;
		}
		v_index++;
	}
	if (player != 1)
		return (false);
	return (true);
}

void	x_y_store(t_data *data, char **map)
{
	int	y_player;
	int	x_player;

	y_player = 0;
	while (map[y_player])
	{
		x_player = 0;
		while (map[y_player][x_player])
		{
			if (player_char(map[y_player][x_player]) == true)
			{
				data->x_p_m = x_player;
				data->y_p_m = y_player;
				return ;
			}
			x_player++;
		}
		y_player++;
	}
}
