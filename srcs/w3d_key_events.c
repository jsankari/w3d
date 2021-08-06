/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_key_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:01:03 by jsankari          #+#    #+#             */
/*   Updated: 2021/05/25 16:49:06 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

int	w3d_key_events(t_wolf *w)
{
	if (w->event.type == SDL_KEYDOWN && w->event.key.keysym.sym == SDLK_ESCAPE)
		return (0);
	else if (w->event.key.keysym.sym == SDLK_LEFT)
		w3d_player_rotate(w, LEFT);
	else if (w->event.key.keysym.sym == SDLK_RIGHT)
		w3d_player_rotate(w, RIGHT);
	else if (w->event.key.keysym.sym == SDLK_UP)
		w3d_player_move(w, UP);
	else if (w->event.key.keysym.sym == SDLK_DOWN)
		w3d_player_move(w, DOWN);
	if (w->player.angle < 0)
		w->player.angle += (float)2 * (float)V_PI;
	else if (w->player.angle > (float)2 * (float)V_PI)
		w->player.angle -= (float)2 * (float)V_PI;
	return (1);
}
