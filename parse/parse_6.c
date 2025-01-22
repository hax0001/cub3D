/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:21:25 by akajjou           #+#    #+#             */
/*   Updated: 2025/01/22 17:27:44 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

bool	file_check(char *file_name)
{
	int	i;
	int	fd;

	i = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	while (file_name[i])
		i++;
	if (ft_strncmp(file_name + i - 4, ".xpm", i))
		return (false);
	return (true);
}

bool	texture_parse(t_data *data)
{
	char	**temp;
	char	*textures[7];
	int		i;

	textures[0] = data->no;
	textures[1] = data->so;
	textures[2] = data->we;
	textures[3] = data->ea;
	textures[4] = data->f;
	textures[5] = data->c;
	textures[6] = NULL;
	i = 0;
	while (textures[i])
	{
		temp = ft_split(textures[i], ' ');
		if (ft_arg_count(temp) != 2)
			return (ft_free_array(temp), false);
		if (file_check(temp[1]) == false)
			return (ft_free_array(temp), false);
		ft_free_array(temp);
		i++;
	}
	return (true);
}

bool	type_id_parse(t_data *data)
{
	if (id_type_parse(data) == false)
		return (false);
	if (texture_parse(data) == false)
		return (false);
	return (true);
}

bool	type_id_storer(t_data *data, char **map)
{
	int	v_index;
	int	end_index;
	int	c_index;

	v_index = 0;
	if (!map)
		return (printf("Error\nInvalid Map\n"), false);
	while (map[v_index])
	{
		skipper(map[v_index], &c_index, &end_index);
		if (ft_strnstr(map[v_index] + c_index, "NO", end_index))
			data->no = ft_strdup(map[v_index] + c_index);
		if (ft_strnstr(map[v_index] + c_index, "SO", end_index))
			data->so = ft_strdup(map[v_index] + c_index);
		if (ft_strnstr(map[v_index] + c_index, "WE", end_index))
			data->we = ft_strdup(map[v_index] + c_index);
		if (ft_strnstr(map[v_index] + c_index, "EA", end_index))
			data->ea = ft_strdup(map[v_index] + c_index);
		v_index++;
	}
	if (type_id_parse(data) == false)
	{
		printf("Error\nInvalid Textures\n");
		return (false);
	}
	return (true);
}

bool	id_color_parse(t_data *data)
{
	int	c_index;
	int	end_index;

	skipper(data->f, &c_index, &end_index);
	if (data->f && ft_strncmp(data->f, "F", end_index) != 0)
		return (false);
	skipper(data->c, &c_index, &end_index);
	if (data->c && ft_strncmp(data->c, "C", end_index) != 0)
		return (false);
	return (true);
}
