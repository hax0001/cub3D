/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:44:17 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/29 00:41:12 by akajjou          ###   ########.fr       */
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

char	*my_mlx_get_data(t_texture *tex)
{
	return (mlx_get_data_addr(tex->img,
			&tex->bits_per_pixel,
			&tex->line_length,
			&tex->endian));
}

void	load_textures(t_global *global)
{
	global->data->north_tex = (t_texture *)ft_malloc(sizeof(t_texture));
	global->data->south_tex = (t_texture *)ft_malloc(sizeof(t_texture));
	global->data->east_tex = (t_texture *)ft_malloc(sizeof(t_texture));
	global->data->west_tex = (t_texture *)ft_malloc(sizeof(t_texture));
	global->data->north_tex->img = mlx_xpm_file_to_image(global->mlx_p,
			ft_path_to_texture(global->data->no),
			&global->data->north_tex->width, &global->data->north_tex->height);
	global->data->south_tex->img = mlx_xpm_file_to_image(global->mlx_p,
			ft_path_to_texture(global->data->so),
			&global->data->south_tex->width, &global->data->south_tex->height);
	global->data->east_tex->img = mlx_xpm_file_to_image(global->mlx_p,
			ft_path_to_texture(global->data->ea),
			&global->data->east_tex->width, &global->data->east_tex->height);
	global->data->west_tex->img = mlx_xpm_file_to_image(global->mlx_p,
			ft_path_to_texture(global->data->we),
			&global->data->west_tex->width, &global->data->west_tex->height);
	global->data->north_tex->addr = my_mlx_get_data(global->data->north_tex);
	global->data->south_tex->addr = my_mlx_get_data(global->data->south_tex);
	global->data->east_tex->addr = my_mlx_get_data(global->data->east_tex);
	global->data->west_tex->addr = my_mlx_get_data(global->data->west_tex);
}
