/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_create_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:36:55 by jsankari          #+#    #+#             */
/*   Updated: 2021/05/25 16:09:01 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

float	w3d_player_angle_to_real_angle(float ray_angle, t_wolf *w)
{
	float	real_angle;

	real_angle = w->player.angle + ray_angle;
	if (real_angle < 0)
		real_angle += (float)2 * V_PI;
	if (real_angle > (float)2 * V_PI)
		real_angle -= (float)2 * V_PI;
	return (real_angle);
}

static void	w3d_fix_fishbowl(float *wall_distance, float ray_angle)
{
	if (wall_distance > 0)
		*wall_distance *= cosf(ray_angle);
}

void	w3d_find_edge(t_wolf *w)
{
	float	ray_angle;
	float	wall_dist;
	float	real_angle;
	int		i;

	i = 0;
	ray_angle = w->ray.angle;
	wall_dist = 0;
	while (i < WIN_WID)
	{
		real_angle = w3d_player_angle_to_real_angle(ray_angle, w);
		wall_dist = w3d_check_lines(i, real_angle, w);
		w3d_fix_fishbowl(&wall_dist, ray_angle);
		if (wall_dist > 0)
			w->wall.height[i] = (float)TILE_SIZE / wall_dist * w->pp_dist;
		else
			w->wall.height[i] = 0;
		ray_angle += w->ray.step;
		i++;
	}
}

void	w3d_copy_bg(t_wolf *w)
{
	UINT	i;
	UINT	max;

	i = 0;
	max = WIN_HEI * WIN_WID;
	while (i < max)
	{
		w->img[i] = w->bg[i];
		i++;
	}
}

void	w3d_create_3d_image(t_wolf *w)
{
	w3d_find_edge(w);
	w3d_copy_bg(w);
	w3d_draw_3d(w, 0, 0);
}
