/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:16:59 by akajjou           #+#    #+#             */
/*   Updated: 2025/01/21 13:24:15 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	w_h_store(t_data *data, char **map)
{
	size_t	w_map;
	int		v_index;

	v_index = 0;
	w_map = ft_strlen(map[v_index]);
	while (map[v_index])
	{
		if (w_map < ft_strlen(map[v_index]))
			w_map = ft_strlen(map[v_index]);
		v_index++;
	}
	data->h_map = ft_arg_count(map);
	data->w_map = w_map;
}

bool	map_check(t_data *data, char **map)
{
	map_writer(data, map);
	if (map_characters_check(data->map) == false)
		return (false);
	if (map_border_check(data->map) == false)
		return (printf("error in border\n"), false);
	if (map_border_updown(data->map) == false)
		return (printf("error in border 2\n"), false);
	if (map_valid_char(data->map) == false)
		return (printf("error in border 3\n"), false);
	player_view(data, data->map);
	x_y_store(data, data->map);
	w_h_store(data, data->map);
	return (true);
}

bool	map_checker(t_data *data, char **map)
{
	if (type_id_storer(data, map) == false)
		return (false);
	if (color_storer(data, map) == false)
		return (false);
	if (map_check(data, map) == false)
		return (false);
	return (true);
}

bool	parses_map(t_global **global, t_data *data, char *FileName)
{
	char	**map;

	data = (t_data *)ft_malloc(sizeof(t_data));
	(*global)->data = data;
	ft_memset(data, 0, sizeof(t_data));
	if (write_map(&map, FileName) == false)
		return (false);
	if (map_checker(data, map) == false)
		return (false);
	return (true);
}

bool	filename_check(int argc, char **argv)
{
	int		lilelen;
	char	*filename;

	if (argc != 2)
	{
		printf("Error\nUsage : ./cub3d <map>\n");
		return (false);
	}
	lilelen = ft_strlen(argv[1]) - 4;
	filename = argv[1];
	if (strcmp(filename + lilelen, ".cub") != 0)
	{
		printf("Error\nBad extension\n");
		return (false);
	}
	return (true);
}
