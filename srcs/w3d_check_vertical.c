/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_check_vertical.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsankari <jsankari@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 19:38:03 by jsankari          #+#    #+#             */
/*   Updated: 2021/06/15 15:00:39 by jsankari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

void	w3d_wall_column(int direction, t_wolf *w)
{
	if (direction == D_NORTH)
		w->hit.north = ((int)w->check.x % TILE_SIZE);
	if (direction == D_EAST)
		w->hit.east = ((int)w->check.y % TILE_SIZE);
	if (direction == D_SOUTH)
		w->hit.south = ((int)w->check.x % TILE_SIZE);
	if (direction == D_WEST)
		w->hit.west = ((int)w->check.y % TILE_SIZE);
}

float	w3d_check_hit(int direction, t_wolf *w)
{
	int		wall;
	int		loc;
	float	wall_distance;

	wall = 0;
	wall_distance = 0;
	loc = (int)w->check.y / TILE_SIZE * \
w->maps.mwid + (int)w->check.x / TILE_SIZE;
	if (direction == D_NORTH)
		wall = w3d_iswall(loc - (w->maps.mwid), w);
	if (direction == D_EAST)
		wall = w3d_iswall(loc - 1, w);
	if (direction == D_SOUTH || direction == D_WEST)
		wall = w3d_iswall(loc, w);
	if (wall == 1)
		wall_distance = w3d_calculate_distance(w->player.x, \
w->player.y, w->check.x, w->check.y);
	w3d_wall_column(direction, w);
	return (wall_distance);
}

float	w3d_check_lines_west(float real_angle, t_wolf *w)
{
	w->check.distance = CHECK_DIST;
	w->wall.dist = 0;
	w->check.offset_x = TILE_SIZE;
	w->check.offset_y = -TILE_SIZE * -tanf(real_angle);
	w->check.x = (((int)w->player.x / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
	w->check.y = (w->player.x - w->check.x) * -tanf(real_angle) + w->player.y;
	while (w->check.distance)
	{
		w->check.boundary = w3d_boundary_check(w);
		if (w->check.boundary == 1)
			break ;
		if (w->check.y > 0 && w->check.x > 0 && w->check.y < w->maps.mhei * \
TILE_SIZE && w->check.x < w->maps.mwid * TILE_SIZE)
		{
			w->wall.dist = w3d_check_hit(D_WEST, w);
			if (w->wall.dist > 0)
				break ;
		}
		w->check.y += w->check.offset_y;
		w->check.x += w->check.offset_x;
		w->check.distance--;
	}
	return (w->wall.dist);
}

float	w3d_check_lines_east(float real_angle, t_wolf *w)
{
	w->check.distance = CHECK_DIST;
	w->wall.dist = 0;
	w->check.offset_x = -TILE_SIZE;
	w->check.offset_y = -w->check.offset_x * -tanf(real_angle);
	w->check.x = (((int)w->player.x / TILE_SIZE) * TILE_SIZE);
	w->check.y = (w->player.x - w->check.x) * -tanf(real_angle) + w->player.y;
	while (w->check.distance)
	{
		w->check.boundary = w3d_boundary_check(w);
		if (w->check.boundary == 1)
			break ;
		if (w->check.y > 0 && w->check.x > 0 && w->check.y < w->maps.mhei * \
TILE_SIZE && w->check.x < w->maps.mwid * TILE_SIZE)
		{
			w->wall.dist = w3d_check_hit(D_EAST, w);
			if (w->wall.dist > 0)
				break ;
		}
		w->check.y += w->check.offset_y;
		w->check.x += w->check.offset_x;
		w->check.distance--;
	}
	return (w->wall.dist);
}

float	w3d_check_lines_vertical(float real_angle, t_wolf *w)
{
	float	distance;
	size_t	hit;

	hit = 0;
	distance = 0;
	if (real_angle < w->pi.north || real_angle > w->pi.south)
	{
		distance = w3d_check_lines_west(real_angle, w);
		hit = D_WEST;
	}
	if (real_angle > w->pi.north && real_angle < w->pi.south)
	{
		distance = w3d_check_lines_east(real_angle, w);
		hit = D_EAST;
	}
	if (hit == D_WEST)
		w->hit.vertical = w->hit.west;
	if (hit == D_EAST)
		w->hit.vertical = w->hit.east;
	return (distance);
}
