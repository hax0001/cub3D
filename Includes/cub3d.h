/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:30:50 by nait-bou          #+#    #+#             */
/*   Updated: 2024/12/17 12:53:08 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "mlx.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "collors.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

# define S_W 1900 // wndow width
# define S_H 1000 // window height
# define TILE_SIZE 30 // size of tile
# define FOV 60 // field of vew
# define R_SPEED 0.045 // rottion speed
# define P_SPEED 4 //player speed

# define ERR_INVALID_ARGUMENT      "Invalid argument provided."
# define ERR_FILE_NOT_FOUND        "File not found."
# define ERR_INVALID_FILE_FORMAT   "Invalid file format."
# define ERR_MEMORY_ALLOCATION     "Memory allocation failed."
# define ERR_INVALID_MAP           "Invalid map configuration."
# define ERR_MLX_INIT_FAILED       "Failed to initialize MLX."
# define ERR_TEXTURE_LOAD_FAILED   "Failed to load texture."
# define ERR_GENERIC               "An unspecified error occurred."

typedef struct s_player
{
    int     x_p; // x player position in pixel
    int     y_p; // y player position in pixel
    double  angle; // player ange
    float   fov; // feild of vew in rotation
    int     r_f; // rotation flag
    int     l_r; // left / right flag
    int     u_d; // up / down flag
} t_player;

typedef struct s_ray
{
    double  angle; // ray angle
    double  distance; // ray distance
    int     ray_f; // ray flag
} t_ray ;

typedef struct s_data
{
    char    **map; // map in 2d demention
    int     x_p_m; // x player position in map
    int     y_p_m; // y player position in map
    int     w_map; // width map
    int     h_map; // hight map
} t_data ;

typedef struct s_global
{
    void    *mlx_p; // mlx pointer
    void    *mlx_w; // mlx window pointer
    void    *mlx_image; // mlx image pointer
    t_list  *gar_co; // head od list of gabedge collector
    t_data  *data; // pointer to data struct
    t_ray   *ray; // pointer to ray struct
    t_player    *player; // ponter to player struct
} t_global ;


extern t_global    *g_global; // global varible to acces t_mlx data struct

//******************gar_co && memory******************* */
void	*ft_malloc(size_t size);
void	ft_free_all(void);
t_global **get_heap(void);
//***************************************************** */

//******************parse****************************** */
t_data  *parse_map();
//***************************************************** */

void    cub3d(void);
void    init_player(void);
void ft_error(char *error_type);



#endif