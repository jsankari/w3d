/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsankari <jsankari@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:12:51 by jsankari          #+#    #+#             */
/*   Updated: 2021/06/15 14:54:28 by jsankari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_H
# define W3D_H

# include <math.h>
# include <fcntl.h>
# include "../libsdl/include/SDL.h"
# include "w3d_defines.h"
# include "../libft/includes/libft.h"

typedef struct s_maps
{
	int		mhei;
	int		mwid;
}			t_maps;

typedef struct s_mir
{
	size_t	i;
	size_t	x;
	size_t	b;
}			t_mir;

typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	int		next;
	int		valid;
	float	angle;
}			t_player;

typedef struct s_ray
{
	float		angle;
	float		step;
}				t_ray;

typedef struct s_wall
{
	int			*direction;
	int			*texture_column;
	int			*height;
	float		dist;
}					t_wall;

typedef struct s_hit
{
	int			north;
	int			south;
	int			east;
	int			west;
	int			vertical;
	int			horizontal;
}				t_hit;

typedef struct s_codes
{
	char	c;
	int		colour;
}			t_codes;

typedef struct s_textures
{
	unsigned int	*north;
	unsigned int	*south;
	unsigned int	*east;
	unsigned int	*west;
	int				amount;
	int				size;
	t_codes			*codes;
}					t_textures;

typedef struct s_check
{
	float	y;
	float	x;
	float	offset_x;
	float	offset_y;
	size_t	distance;
	int		boundary;

}			t_check;

typedef struct s_pi
{
	float	north;
	float	south;
	float	east;
	float	west;
}			t_pi;

typedef struct s_wolf
{
	SDL_Window		*win_ptr;
	SDL_Event		event;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	char			*map;
	int				*imap;
	unsigned int	*img;
	unsigned int	*bg;
	int				img_size;
	float			pp_dist;
	float			wall_dist_horizontal;
	float			wall_dist_vertical;
	float			wall_dist;
	t_check			check;
	t_maps			maps;
	t_player		player;
	t_ray			ray;
	t_wall			wall;
	t_textures		textures;
	t_hit			hit;
	t_pi			pi;
}					t_wolf;

int		w3d_validate_map(char *filename, t_wolf *w);
float	w3d_check_lines(int i, float real_angle, t_wolf *w);
int		w3d_key_events(t_wolf *w);
int		w3d_map_reader(char *filename, t_wolf *w);
void	w3d_draw_background(t_wolf *w);
float	w3d_check_lines_vertical(float real_angle, t_wolf *w);
float	w3d_check_lines_horizontal(float real_angle, t_wolf *w);
float	w3d_calculate_distance(float px, float py, float cx, float cy);
int		w3d_iswall(int loc, t_wolf *w);
void	w3d_draw_3d(t_wolf *w, int x, int y);
void	w3d_create_3d_image(t_wolf *w);
void	w3d_textures(t_wolf *w);
void	die(char *reason);
int		w3d_set_player_start(t_wolf *w);
UINT	*w3d_texture_map(t_textures *t, UINT *save, int file);
void	w3d_texture_codes(t_textures *t, int file, int i);
float	w3d_check_hit(int direction, t_wolf *w);
int		w3d_boundary_check(t_wolf *w);
int		w3d_calculate_wall_bottom(int i, t_wolf *w);
int		w3d_calculate_wall_top(int i, t_wolf *w);
void	w3d_player_move(t_wolf *w, int dir);
void	w3d_player_rotate(t_wolf *w, int dir);
void	w3d_create_map(char *map_file, t_wolf *w);

#endif
