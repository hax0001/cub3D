/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:26:26 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/13 14:44:41 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"



bool        write_map(char ***maps, char *FileName) // this fct read the file only and return it in a double array
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


void        skipper(char *line, int *c_index, int *end_index)
{
    int     index;

    *c_index = 0;
    *end_index = 0;
    index = 0;
    while (line[index] && line[index] == ' ')
    {
        (*c_index)++;
        index++;    
    }
    while (line[index] && ft_isalpha(line[index]) )
        index++;
    (*end_index) = index;
}

bool    id_names(t_data *data)
{
    int    c_index;
    int    end_index;

    skipper(data->no, &c_index, &end_index);
    if (!ft_strncmp(data->no, "NO", end_index))
        return ( printf("%s\n", data->no + end_index),false);
    skipper(data->ea, &c_index, &end_index);
    if (!ft_strncmp(data->ea, "EA", end_index))
        return ( printf("EA\n"),false);
    skipper(data->we, &c_index, &end_index);
    if (!ft_strncmp(data->we, "WE", end_index))
        return ( printf("WE\n"),false);
    skipper(data->so, &c_index, &end_index);    
    if (!ft_strncmp(data->so, "SO", end_index))
        return ( printf("SO\n"),false);
    return (true);
}

bool    type_id_parse(t_data *data)
{

    if (id_names(data) == false)
        return (false);
    return (true);
}

bool    type_id_storer(t_data *data, char **map)
{
    int     v_index;
    int     end_index;
    int     c_index;

    v_index = 0;
    while (map[v_index])
    {
        skipper(map[v_index],&c_index, &end_index);
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
        printf("Error\nInvalide Textures\n");
        return (false);
    }
    return (true);
}

bool    color_storer(t_data *data, char **map)
{
    int     v_index;
    int     end_index;
    int     c_index;

    v_index = 0;
    while (map[v_index])
    {
        skipper(map[v_index],&c_index, &end_index);
        if (ft_strnstr(map[v_index] + c_index, "C", end_index))
            data->c = ft_strdup(map[v_index] + c_index);
        if (ft_strnstr(map[v_index] + c_index, "F", end_index))
            data->f = ft_strdup(map[v_index] + c_index);
        v_index++;
    }
    return (true);
}


bool    map_checker(t_data *data, char    **map)
{
    if (type_id_storer(data, map) == false)
        return (false);
    if (color_storer(data, map) == false)
        return (false);
    // if (map_check(data, map) == false)
    //     return (false);
    // printf("%s\n%s\n%s\n%s\n%s\n%s\n",data->no,data->ea,data->so,data->we, data->c, data->f);    
    return (true);
}


bool    parses_map(t_data *data,char *FileName) // this fct will check if we have a valid map
{
    char **map;
    data = (t_data *)ft_malloc(sizeof(t_data));
    ft_memset(data, 0, sizeof(t_data));
    if (write_map(&map, FileName) == false)
        return (false);
    if (map_checker(data, map) == false)
        return (false);

    return (true);
}
bool    FileName_check( int argc, char **argv) // this fct check only the FileName extesion 
{
    int     FileLen;
    char    *FileName;
    
    if (argc != 2)
    {
        printf("Error\nUsage : ./cub3d <map>\n");
        return (false);
    }
    FileLen = strlen(argv[1]) - 4;
    FileName = argv[1];
    if (strcmp( FileName + FileLen, ".cub") != 0)
    {   
        printf("Error\nBad extension\n");
        return (false);
    }   
    return (true);
}
