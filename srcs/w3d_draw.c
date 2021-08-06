/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:43:03 by jsankari          #+#    #+#             */
/*   Updated: 2021/05/25 16:13:46 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

/*
** Saves the background into an easily copiable UINT array.
*/

void	w3d_draw_background(t_wolf *w)
{
	int	i;

	i = 0;
	while (i < WIN_WID * WIN_HEI - 1)
	{
		if (i < WIN_HEI * WIN_WID * 0.5)
			w->bg[i] = C_SKY;
		else if (i >= WIN_HEI * WIN_WID * 0.5)
			w->bg[i] = C_GREY;
		i++;
	}
}

void	w3d_draw_texture(int i, int y, float texture_y, t_wolf *w)
{
	if (w->wall.direction[i] == 1)
		w->img[y * WIN_WID + i] = w->textures.north[TILE_SIZE * (int)texture_y
			+ w->wall.texture_column[i]];
	else if (w->wall.direction[i] == 2)
		w->img[y * WIN_WID + i] = w->textures.south[TILE_SIZE * (int)texture_y
			+ w->wall.texture_column[i]];
	else if (w->wall.direction[i] == 3)
		w->img[y * WIN_WID + i] = w->textures.east[TILE_SIZE * (int)texture_y
			+ w->wall.texture_column[i]];
	else if (w->wall.direction[i] == 4)
		w->img[y * WIN_WID + i] = w->textures.west[TILE_SIZE * (int)texture_y
			+ w->wall.texture_column[i]];
}

float	w3d_texture_step(int i, int texture_size, t_wolf *w)
{
	float	step;

	step = (float)texture_size / (float)w->wall.height[i];
	return (step);
}

float	w3d_texture_start(int i, int bottom, float texture_step, t_wolf *w)
{
	float	texture_start;

	texture_start = (bottom - WIN_HEI * 0.5f + w->wall.height[i] * 0.5f)
		* texture_step;
	return (texture_start);
}

/*
** Draws map. Takes in the starting points of x and y.
*/

void	w3d_draw_3d(t_wolf *w, int x, int y)
{
	int		top;
	int		bottom;
	float	texture_y;
	float	texture_step;

	while (x < WIN_WID)
	{
		bottom = w3d_calculate_wall_bottom(x, w);
		top = w3d_calculate_wall_top(x, w);
		texture_step = w3d_texture_step(x, TILE_SIZE, w);
		texture_y = w3d_texture_start(x, bottom, texture_step, w);
		y = bottom;
		while (y < top)
		{
			w3d_draw_texture(x, y, texture_y, w);
			texture_y += texture_step;
			y++;
		}
		x++;
	}
}
