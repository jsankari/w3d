/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:54:02 by jsankari          #+#    #+#             */
/*   Updated: 2021/05/25 15:41:39 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

int	w3d_iswall(int loc, t_wolf *w)
{
	if (w->imap[loc] == 1)
		return (1);
	return (0);
}

float	w3d_choose_smaller_distance(float num1, float num2)
{
	if (num1 == 0 && num2 == 0)
		return (0);
	else if (num1 == 0)
		return (num2);
	else if (num2 == 0)
		return (num1);
	else if (num1 < num2)
		return (num1);
	else if (num2 < num1)
		return (num2);
	else if (num2 == num1)
		return (num1);
	return (0);
}

float	w3d_calculate_distance(float px, float py, float cx, float cy)
{
	float	a;
	float	b;
	float	distance;

	a = (px - cx) * (px - cx);
	b = (py - cy) * (py - cy);
	distance = sqrtf(a + b);
	return (distance);
}

int	w3d_select_wall_texture(int i, float real_angle, t_wolf *w)
{
	if (real_angle > V_PI && w->wall_dist == w->wall_dist_horizontal)
	{
		w->wall.texture_column[i] = w->hit.horizontal;
		return (1);
	}
	else if (real_angle < V_PI && w->wall_dist == w->wall_dist_horizontal)
	{
		w->wall.texture_column[i] = w->hit.horizontal;
		return (2);
	}
	else if ((real_angle < V_PI * (float)0.5
			|| real_angle > (float)3 * V_PI * (float)0.5)
		&& w->wall_dist == w->wall_dist_vertical)
	{
		w->wall.texture_column[i] = w->hit.vertical;
		return (3);
	}
	else if (real_angle > V_PI * (float)0.5
		&& real_angle < (float)3 * V_PI * (float)0.5
		&& w->wall_dist == w->wall_dist_vertical)
	{
		w->wall.texture_column[i] = w->hit.vertical;
		return (4);
	}
	return (0);
}

float	w3d_check_lines(int i, float real_angle, t_wolf *w)
{
	w->wall_dist_horizontal = 0;
	w->wall_dist_vertical = 0;
	w->wall_dist = 0;
	w->wall_dist_horizontal = w3d_check_lines_horizontal(real_angle, w);
	w->wall_dist_vertical = w3d_check_lines_vertical(real_angle, w);
	w->wall_dist = w3d_choose_smaller_distance(w->wall_dist_horizontal,
			w->wall_dist_vertical);
	w->wall.direction[i] = w3d_select_wall_texture(i, real_angle, w);
	return (w->wall_dist);
}
