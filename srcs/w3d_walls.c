/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:11:52 by esormune          #+#    #+#             */
/*   Updated: 2021/05/25 16:13:14 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

int	w3d_calculate_wall_bottom(int i, t_wolf *w)
{
	int	bottom;

	bottom = -w->wall.height[i] * 0.5f + WIN_HEI * 0.5f;
	if (bottom < 0)
		bottom = 0;
	return (bottom);
}

int	w3d_calculate_wall_top(int i, t_wolf *w)
{
	int	top;

	top = w->wall.height[i] * 0.5f + WIN_HEI * 0.5f;
	if (top > WIN_HEI - 1)
		top = WIN_HEI - 1;
	return (top);
}
