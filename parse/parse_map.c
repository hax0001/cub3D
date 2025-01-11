/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:26:26 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/11 22:52:39 by akajjou          ###   ########.fr       */
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

bool    map_checker(char **map) // this fct will ... mzl ma3rft
{
    return (true);
}

bool    parses_map(char *FileName) // this fct will check if we have a valid map
{
    char **map;
    
    if (write_map(&map, FileName) == false)
        return (false);
    if (map_check(map) == false)
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
