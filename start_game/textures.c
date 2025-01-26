/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:44:17 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/26 01:14:48 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

char	*ft_path_to_texture(char *str)
{
	char	**texture;
	char	*ret_texture;

	texture = ft_split(str, ' ');
	ret_texture = ft_strdup(texture[1]);
	return (ret_texture);
}

void load_textures(t_global *global) { // taaaaaaaaaaaaaaake
    int tex_width, tex_height;

    global->data->north_tex = (t_texture *)ft_malloc(sizeof(t_texture)); 
    global->data->south_tex = (t_texture *)ft_malloc(sizeof(t_texture)); 
    global->data->east_tex = (t_texture *)ft_malloc(sizeof(t_texture)); 
    global->data->west_tex = (t_texture *)ft_malloc(sizeof(t_texture)); 
    
    global->data->north_tex->img = mlx_xpm_file_to_image(global->mlx_p, "soul_sand.xpm", &tex_width, &tex_height);
    global->data->south_tex->img = mlx_xpm_file_to_image(global->mlx_p, "soul_sand.xpm", &tex_width, &tex_height);
    global->data->east_tex->img = mlx_xpm_file_to_image(global->mlx_p, "soul_sand.xpm", &tex_width, &tex_height);
    global->data->west_tex->img = mlx_xpm_file_to_image(global->mlx_p, "soul_sand.xpm", &tex_width, &tex_height);

    global->data->north_tex->addr = mlx_get_data_addr(global->data->north_tex->img, &global->data->north_tex->bits_per_pixel, &global->data->north_tex->line_length, &global->data->north_tex->endian);
    global->data->south_tex->addr = mlx_get_data_addr(global->data->south_tex->img, &global->data->south_tex->bits_per_pixel, &global->data->south_tex->line_length, &global->data->south_tex->endian);
    global->data->east_tex->addr = mlx_get_data_addr(global->data->east_tex->img, &global->data->east_tex->bits_per_pixel, &global->data->east_tex->line_length, &global->data->east_tex->endian);
   global->data->west_tex->addr = mlx_get_data_addr(global->data->west_tex->img, &global->data->west_tex->bits_per_pixel, &global->data->west_tex->line_length, &global->data->west_tex->endian);


}
