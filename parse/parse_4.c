/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:18:07 by akajjou           #+#    #+#             */
/*   Updated: 2025/01/20 22:21:33 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

bool	color_parse(t_data *data)
{
	if (id_color_parse(data) == false)
		return (false);
	if (color_range_parse(data, data->f, data->c) == false)
		return (false);
	return (true);
}

bool	color_storer(t_data *data, char **map)
{
	int	v_index;
	int	end_index;
	int	c_index;

	v_index = 0;
	while (map[v_index])
	{
		skipper(map[v_index], &c_index, &end_index);
		if (ft_strnstr(map[v_index] + c_index, "C", end_index))
			data->c = ft_strdup(map[v_index] + c_index);
		if (ft_strnstr(map[v_index] + c_index, "F", end_index))
			data->f = ft_strdup(map[v_index] + c_index);
		v_index++;
	}
	if (color_parse(data) == false)
	{
		printf("Error\nInvalid Colors\n");
		return (false);
	}
	return (true);
}

bool	is_white_space(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

bool	map_end(char *line)
{
	char	**line_splite;

	line_splite = ft_split(line, ' ');
	if (!strcmp(line_splite[0], "F") || !strcmp(line_splite[0], "C")
		|| !strcmp(line_splite[0], "SO") || !strcmp(line_splite[0], "NO")
		|| !strcmp(line_splite[0], "WE") || !strcmp(line_splite[0], "EA"))
		return (true);
	return (false);
}

void	map_writer(t_data *data, char **map)
{
	int	index;
	int	map_index;

	map_index = 0;
	index = 0;
	while (map[index])
		index++;
	index--;
	while (map[index])
	{
		if (is_white_space(map[index]) == true || map_end(map[index]) == true)
			break ;
		index--;
	}
	index++;
	data->map = (char **)malloc((ft_arg_count(map) - index)
			* sizeof(char **));
	data->map[ft_arg_count(map) - index] = NULL;
	while (map[index])
		data->map[map_index++] = ft_strdup(map[index++]);
}
