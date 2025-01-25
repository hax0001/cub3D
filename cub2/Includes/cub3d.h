/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:30:50 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/26 00:31:31 by nait-bou         ###   ########.fr       */
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
# include <stdbool.h>
# include "collors.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define MINIMAP_SIZE 200  // Size of minimap in pixels
#define MINIMAP_SCALE 0.25 // Scale factor for minimap (1/5 of original size)
#define MINIMAP_PADDING 3

# define S_W 1900 // wndow width
# define S_H 1000 // window height
# define TILE_SIZE 30 // size of tile
# define FOV 70 // field of vew
# define R_SPEED 0.020 // rottion speed
# define P_SPEED 2 //player speed

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
    double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
    
} t_ray ;

typedef struct s_texture {
    void    *img;           // MLX image pointer
    char    *addr;          // Image data address
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
} t_texture;

typedef struct s_draw_info
{
	t_texture	*tex;
	int			b_pix;
	int			tex_x;
}	t_draw_info;

typedef struct s_data
{
    char             **map; // map in 2d demention
    char             *no;
    char             *so;
    char             *we;
    char             *ea;
    char             *f;
    char             *c;
    int              angle;
    unsigned int     c_color;
    unsigned int     f_color;
    int              x_p_m; // x player position in map
    int              y_p_m; // y player position in map
    int              w_map; // width map
    int              h_map; // hight map
    t_texture        *north_tex;
    t_texture        *south_tex;
    t_texture        *east_tex;
    t_texture        *west_tex;
} t_data ;


typedef struct s_global
{
    void    *mlx_p; // mlx pointer
    void    *mlx_w; // mlx window pointer
    void    *mlx_image; // mlx image pointer
    void    *mlx_image2; // mlx image pointer

    t_list  *gar_co; // head od list of gabedge collector
    t_data  *data; // pointer to data struct
    t_ray   *ray; // pointer to ray struct
    t_player    *player; // ponter to player struct
} t_global ;


//******************gar_co && memory******************* */
void draw_minimap(t_global *global);
void	*ft_malloc(size_t size);
void	ft_free_all(void);
void init_textures(t_global *global);
void print_data(t_data *data);
t_global **get_heap(void);
//***************************************************** */

//******************parse****************************** */
void    ft_free_array(char **array);
bool    write_map(char ***maps, char *FileName);
void    skipper(char *line, int *c_index, int *end_index);
bool    id_type_parse(t_data *data);
int     ft_arg_count(char **texture);
bool    file_check(char *file_name);
bool    texture_parse(t_data *data);
bool    type_id_parse(t_data *data);
bool    type_id_storer(t_data *data, char **map);
bool    id_color_parse(t_data *data);
bool    in_range(char *color);
bool    is_valid_color(char *color_tmp);
unsigned int    rgb_to_hex(int r, int g, int b);
void    color_converter(t_data *data, char *floor_arg, char *ceiling_arg);
bool    color_range_parse(t_data *data, char *floor_arg, char *ceiling_arg);
bool    color_parse(t_data *data);
bool    color_storer(t_data *data, char **map);
bool    is_white_space(char *line);
bool    map_end(char *line);
void    map_writer(t_data *data, char **map);
bool    line_char_check(char *line);
bool    map_characters_check(char **map);
bool    all_one(char *line);
bool    border_check(char *line);
bool    map_border_check(char **map);
bool    player_char(char c);
bool    map_border_updown(char **map);
void    player_view(t_data *data, char **map);
bool    map_valid_char(char **map);
void    x_y_store(t_data *data, char **map);
void    w_h_store(t_data *data, char **map);
bool    map_check(t_data *data, char **map);
bool    map_checker(t_data *data, char **map);
bool    parses_map(t_global **global, t_data *data, char *FileName);
bool    filename_check(int argc, char **argv);
//***************************************************** */

void    cub3d(void);
void    init_player(void);
void ft_error(char *error_type);

void cast_rays();
void draw_map(void);
void render_wall(int ray);
int	key_press(int keycode, void *info);
void    ft_exit(void);
int key_release(int keycode, void *info);
void	mouve(t_global *global ,double mouve_x ,double mouve_y); 
void load_textures(t_global *global);

#endif