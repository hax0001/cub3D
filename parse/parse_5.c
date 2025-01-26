/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:18:13 by akajjou           #+#    #+#             */
/*   Updated: 2025/01/25 18:57:33 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

bool	in_range(char *color)
{
	size_t	i;

	i = 0;
	while (color[i] && (ft_isdigit(color[i]) == true || color[i] == ','))
		i++;
	if (i != ft_strlen(color))
		return (false);
	return (true);
}

bool	is_valid_color(char *color_tmp)
{
	int		index;
	int		convert_color;
	char	**color;
	char	*color_num[4];

	index = 0;
	color = ft_split(color_tmp, ',');
	if (ft_arg_count(color) != 3 || color_tmp[ft_strlen(color_tmp) - 1] == ','
		|| color_tmp[0] == ',')
		return ( false);
	color_num[0] = color[0];
	color_num[1] = color[1];
	color_num[2] = color[2];
	color_num[3] = NULL;
	while (color_num[index])
	{
		convert_color = ft_atoi(color[index++]);
		if (convert_color >= 0 && convert_color <= 255)
			continue ;
		return ( false);
	}
	return ( true);
}

unsigned int	rgb_to_hex(int r, int g, int b)
{
	return (((unsigned char)r << 16)
		| ((unsigned char)g << 8) | (unsigned char)b);
}

void	color_converter(t_data *data, char *floor_arg, char *ceiling_arg)
{
	char	**ceiling;
	char	**floor;

	ceiling = ft_split(floor_arg, ',');
	floor = ft_split(ceiling_arg, ',');
	data->c_color = rgb_to_hex(ft_atoi(ceiling[0]), ft_atoi(ceiling[1]),
			ft_atoi(ceiling[2]));
	data->f_color = rgb_to_hex(ft_atoi(floor[0]), ft_atoi(floor[1]),
			ft_atoi(floor[2]));
}

bool	color_range_parse(t_data *data, char *floor_arg, char *ceiling_arg)
{
	char	**floor;
	char	**ceiling;

	if (!floor_arg || !ceiling_arg)
		return (false);
	floor = ft_split(floor_arg, ' ');
	ceiling = ft_split(ceiling_arg, ' ');
	if (ft_arg_count(ceiling) != 2 || ft_arg_count(floor) != 2)
		return ( false);
	if (in_range(floor[1]) == false || in_range(ceiling[1]) == false)
		return (false);
	if (is_valid_color(floor[1]) == false
		|| is_valid_color(ceiling[1]) == false)
		return ( false);
	color_converter(data, floor[1], ceiling[1]);
	return (true);
}
