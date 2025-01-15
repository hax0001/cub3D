/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:26:26 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/15 23:36:12 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void    ft_free_array(char **array)
{
    int     i;

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
    if (!line)
        return;
    while (line[index] && line[index] == ' ')
    {
        (*c_index)++;
        index++;    
    }
    while (line[index] && ft_isprint(line[index]) && line[index] != ' ')
        index++;
    (*end_index) = index;
}

bool    id_type_parse(t_data *data)
{
    int    c_index;
    int    end_index;

    skipper(data->no, &c_index, &end_index);
    if (ft_strncmp(data->no, "NO", end_index) != 0)
        return ( false);
    skipper(data->ea, &c_index, &end_index);
    if (ft_strncmp(data->ea, "EA", end_index) != 0)
        return ( false);
    skipper(data->we, &c_index, &end_index);
    if (ft_strncmp(data->we, "WE", end_index) != 0)
        return ( false);
    skipper(data->so, &c_index, &end_index);
    if (ft_strncmp(data->so, "SO", end_index) != 0)
        return ( false);
    return (true);
}

int     ft_arg_count(char **texture)
{
    int     count;

    count = 0;
    while (texture[count])
        count++;    
    return (count);
}

bool    file_check(char     *file_name)
{
    int     i;
    int     fd;

    i = 0;
    fd = open(file_name, O_RDONLY);
    if (fd == -1)
        return (false);
    close (fd);
    while (file_name[i])
        i++;
    if (ft_strncmp(file_name + i - 4, ".xpm", i))
        return (false);
    return (true);
}

bool    texture_parse(t_data *data)
{
    char    **temp;
    char    *textures[7];
    int     i;

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

bool    type_id_parse(t_data *data)
{
    if (id_type_parse(data) == false)
        return (false);
    if (texture_parse(data) == false)
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
        printf("Error\nInvalid Textures\n");
        return (false);
    }
    return (true);
}

bool    id_color_parse(t_data *data)
{
    int    c_index;
    int    end_index;

    skipper(data->f, &c_index, &end_index);
    if (ft_strncmp(data->f, "F", end_index) != 0)
        return ( false);
    skipper(data->c, &c_index, &end_index);
    if (ft_strncmp(data->c, "C", end_index) != 0)
        return ( false);
    return (true);
}

bool    in_range(char *color)
{
    size_t     i;

    i = 0;
    while (color[i] && (ft_isdigit(color[i]) == true || color[i] == ','))
        i++;
    if (i != strlen(color))
        return (false);
    return (true);    
}

bool    is_valid_color(char  *color_tmp)
{
    int     index;
    int     convert_color;
    char    **color;
    char    *color_num[4];

    index = 0;
    color = ft_split(color_tmp, ',');
    if (ft_arg_count(color) != 3 || color_tmp[strlen(color_tmp) - 1] == ',' || color_tmp[0] == ',')
        return (ft_free_array(color), false);
    color_num[0] = color[0];
    color_num[1] = color[1];
    color_num[2] = color[2];
    color_num[3] = NULL;
    while (color_num[index])
    {
        convert_color = ft_atoi(color[index++]);
        if (convert_color >= 0 && convert_color <= 255)
            continue;
        return (ft_free_array(color), false);            
    }
    return (ft_free_array(color), true);
}

unsigned int    rgb_to_hex(int r, int g, int b)
{
    return (((unsigned char)r << 16) | ((unsigned char)g << 8) | (unsigned char)b);
}     

void    color_converter(t_data  *data, char *floor_arg, char *ceiling_arg)
{
    char    **ceiling;
    char    **floor;

    ceiling = ft_split(floor_arg, ',');
    floor   = ft_split(ceiling_arg, ',');
    data->c_color = rgb_to_hex(ft_atoi(ceiling[0]), ft_atoi(ceiling[1]), ft_atoi(ceiling[2]));
    data->f_color = rgb_to_hex(ft_atoi(floor[0]), ft_atoi(floor[1]), ft_atoi(floor[2]));
}
bool    color_range_parse(t_data    *data, char *floor_arg, char *ceiling_arg)
{
    char    **floor;
    char    **ceiling;

    floor = ft_split(floor_arg, ' ');
    ceiling = ft_split(ceiling_arg, ' ');

    if (ft_arg_count(ceiling) != 2 || ft_arg_count(floor)!= 2)
        return (ft_free_array(ceiling), ft_free_array(floor),false);
    if (in_range(floor[1]) == false || in_range(ceiling[1]) == false)
        return (ft_free_array(ceiling), ft_free_array(floor), false);
    if (is_valid_color(floor[1]) == false || is_valid_color(ceiling[1]) == false)
        return (ft_free_array(ceiling), ft_free_array(floor), false);
    color_converter(data, floor[1], ceiling[1]);
    return (true);    
}


bool    color_parse(t_data *data)
{
    if (id_color_parse(data) == false)
        return (false);
    if (color_range_parse(data, data->f, data->c) == false)
        return (false);
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
    if (color_parse(data) == false)
    {
        printf("Error\nInvalid Colors\n");
        return (false);
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
    print_data(data);

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
