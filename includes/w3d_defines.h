/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_defines.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 18:02:47 by jsankari          #+#    #+#             */
/*   Updated: 2021/06/15 16:02:34 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_DEFINES_H
# define W3D_DEFINES_H

# define MAP_PATH	"./maps/map"
# define WIN_WID	640
# define WIN_HEI	480
# define TILE_SIZE	64
# define FOV		60
# define V_PI		3.141592653589793f
# define CHECK_DIST 300

# define C_PURPLE	0x8B00FFFF
# define C_INDIGO	0x2E2B5FFF
# define C_BLUE		0x0000FFFF
# define C_SKY		0x87CEEBFF
# define C_GREEN	0x008000FF
# define C_LIME		0x00FF00FF
# define C_YELLOW	0xFFFF00FF
# define C_ORANGE	0xFF7F00FF
# define C_RED		0xFF0000FF
# define C_BURGUNDY	0x800020FF
# define C_BLOOD	0x732039FF
# define C_GREY		0x696969FF

# define D_NORTH	1
# define D_EAST		2
# define D_SOUTH	3
# define D_WEST		4

# define UINT unsigned int

# define N_TXTR "./textures/bloom64.xpm"
# define E_TXTR "./textures/flight64.xpm"
# define S_TXTR "./textures/pollock64.xpm"
# define W_TXTR "./textures/moonlight64.xpm"

# define LEFT 1
# define RIGHT 2
# define UP 3
# define DOWN 4

#endif
