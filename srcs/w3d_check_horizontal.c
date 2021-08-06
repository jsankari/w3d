/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_check_horizontal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsankari <jsankari@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 19:37:41 by jsankari          #+#    #+#             */
/*   Updated: 2021/06/15 14:57:22 by jsankari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

int	w3d_boundary_check(t_wolf *w)
{
	if ((int)w->check.y / TILE_SIZE > w->maps.mhei - 1)
		return (1);
	if ((int)w->check.x / TILE_SIZE > w->maps.mwid - 1)
		return (1);
	if ((int)w->check.y / TILE_SIZE < 0)
		return (1);
	if ((int)w->check.x / TILE_SIZE < 0)
		return (1);
	return (0);
}

float	w3d_check_lines_north(float real_angle, t_wolf *w)
{
	w->wall.dist = 0;
	w->check.distance = CHECK_DIST;
	w->check.offset_y = -TILE_SIZE;
	w->check.offset_x = -w->check.offset_y * (-1 / tanf(real_angle));
	w->check.y = (((int)w->player.y / TILE_SIZE) * TILE_SIZE);
	w->check.x = (w->player.y - w->check.y) * (-1 / \
tanf(real_angle)) + w->player.x;
	while (w->check.distance)
	{
		w->check.boundary = w3d_boundary_check(w);
		if (w->check.boundary == 1)
			break ;
		if (w->check.y > 0 && w->check.x > 0 && \
w->check.y < w->maps.mhei * TILE_SIZE && w->check.x < w->maps.mwid * TILE_SIZE)
		{
			w->wall.dist = w3d_check_hit(D_NORTH, w);
			if (w->wall.dist > 0)
				break ;
		}
		w->check.y += w->check.offset_y;
		w->check.x += w->check.offset_x;
		w->check.distance--;
	}	
	return (w->wall.dist);
}

float	w3d_check_lines_south(float real_angle, t_wolf *w)
{
	w->wall.dist = 0;
	w->check.distance = CHECK_DIST;
	w->check.offset_y = TILE_SIZE;
	w->check.offset_x = -w->check.offset_y * (-1 / tanf(real_angle));
	w->check.y = (((int)w->player.y / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
	w->check.x = (w->player.y - w->check.y) * (-1 / \
tanf(real_angle)) + w->player.x;
	while (w->check.distance)
	{
		w->check.boundary = w3d_boundary_check(w);
		if (w->check.boundary == 1)
			break ;
		if (w->check.y > 0 && w->check.x > 0 && w->check.y < w->maps.mhei * \
TILE_SIZE && w->check.x < w->maps.mwid * TILE_SIZE)
		{
			w->wall.dist = w3d_check_hit(D_SOUTH, w);
			if (w->wall.dist > 0)
				break ;
		}
		w->check.y += w->check.offset_y;
		w->check.x += w->check.offset_x;
		w->check.distance--;
	}
	return (w->wall.dist);
}

float	w3d_check_lines_horizontal(float real_angle, t_wolf *w)
{
	float	distance;
	size_t	hit;

	hit = 0;
	distance = 0;
	if (real_angle > V_PI)
	{
		distance = w3d_check_lines_north(real_angle, w);
		hit = D_NORTH;
	}
	else if (real_angle < V_PI)
	{
		distance = w3d_check_lines_south(real_angle, w);
		hit = D_SOUTH;
	}
	if (hit == D_NORTH)
		w->hit.horizontal = w->hit.north;
	if (hit == D_SOUTH)
		w->hit.horizontal = w->hit.south;
	return (distance);
}
