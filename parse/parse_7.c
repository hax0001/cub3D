/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:21:36 by akajjou           #+#    #+#             */
/*   Updated: 2025/01/21 12:58:31 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

bool	write_map(char ***maps, char *FileName)
{
	char	*str1;
	int		fd;
	char	*str2;
	char	*tmp;

	str2 = 0;
	fd = open(FileName, O_RDWR);
	str1 = get_next_line(fd);
	if (fd == -1 && str1 == NULL)
	{
		printf("Error\nFatal Error While Reading The File\n");
		return (false);
	}
	while (str1)
	{
		tmp = ft_strjoin(str2, str1);
		free(str2);
		str2 = tmp;
		free(str1);
		str1 = get_next_line(fd);
	}
	close(fd);
	*maps = ft_split(str2, '\n');
	return (free(str2), true);
}

void	skipper(char *line, int *c_index, int *end_index)
{
	int	index;

	*c_index = 0;
	*end_index = 0;
	index = 0;
	if (!line)
		return ;
	while (line[index] && line[index] == ' ')
	{
		(*c_index)++;
		index++;
	}
	while (line[index] && ft_isprint(line[index]) && line[index] != ' ')
		index++;
	(*end_index) = index;
}

bool	id_type_parse(t_data *data)
{
	int	c_index;
	int	end_index;

	skipper(data->no, &c_index, &end_index);
	if (data->no && ft_strncmp(data->no, "NO", end_index) != 0)
		return (false);
	skipper(data->ea, &c_index, &end_index);
	if (data->ea && ft_strncmp(data->ea, "EA", end_index) != 0)
		return (false);
	skipper(data->we, &c_index, &end_index);
	if (data->we && ft_strncmp(data->we, "WE", end_index) != 0)
		return (false);
	skipper(data->so, &c_index, &end_index);
	if (data->so && ft_strncmp(data->so, "SO", end_index) != 0)
		return (false);
	return (true);
}

int	ft_arg_count(char **texture)
{
	int	count;

	if (!texture)
		return (0);
	count = 0;
	while (texture[count])
		count++;
	return (count);
}
