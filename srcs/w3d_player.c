/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:10:54 by esormune          #+#    #+#             */
/*   Updated: 2021/05/25 16:50:53 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

int	w3d_set_player_start(t_wolf *w)
{
	int	map_index;
	int	index_x;
	int	index_y;

	index_x = 0;
	index_y = 0;
	map_index = 0;
	while (index_y < w->maps.mhei)
	{
		index_x = 0;
		while (index_x < w->maps.mwid)
		{
			if (w->imap[map_index] == 2)
			{
				w->player.x = index_x * TILE_SIZE + (TILE_SIZE * 0.5f);
				w->player.y = index_y * TILE_SIZE + (TILE_SIZE * 0.5f);
				w->imap[map_index] = 0;
			}
			map_index++;
			index_x++;
		}
		index_y++;
	}
	return (0);
}

void	w3d_player_rotate(t_wolf *w, int dir)
{
	if (dir == LEFT)
		w->player.angle -= w->ray.step * 20;
	else
		w->player.angle += w->ray.step * 20;
	w->player.dx = cosf(w->player.angle) * 10.0f;
	w->player.dy = sinf(w->player.angle) * 10.0f;
}

int	w3d_validate_player_move(t_wolf *w)
{
	int	tile;

	tile = TILE_SIZE - 1;
	if (w->event.key.keysym.sym == SDLK_UP)
		w->player.next = (int)(w->player.y + w->player.dy) / \
TILE_SIZE * w->maps.mwid + (int)(w->player.x + w->player.dx) / TILE_SIZE;
	else if (w->event.key.keysym.sym == SDLK_DOWN)
		w->player.next = (int)(w->player.y - w->player.dy) / \
TILE_SIZE * w->maps.mwid + (int)(w->player.x - w->player.dx) / TILE_SIZE;
	if (w->imap[w->player.next] == 1)
		return (1);
	if (w->player.next < 0 || w->player.next > w->maps.mhei * w->maps.mwid)
		return (1);
	if (w->event.key.keysym.sym == SDLK_UP && (((w->player.y + w->player.dy)
				> (w->maps.mhei * tile) || (w->player.y + w->player.dy) < 0)
			|| ((w->player.x + w->player.dx) > (w->maps.mwid * tile)
				|| (w->player.x + w->player.dx) < 0)))
		return (1);
	if (w->event.key.keysym.sym == SDLK_DOWN && (((w->player.y - w->player.dy)
				> (w->maps.mhei * tile) || (w->player.y - w->player.dy) < 0)
			|| ((w->player.x - w->player.dx) > (w->maps.mwid * tile)
				|| (w->player.x - w->player.dx) < 0)))
		return (1);
	return (0);
}

void	w3d_player_move(t_wolf *w, int dir)
{
	w->player.valid = w3d_validate_player_move(w);
	if (w->player.valid == 0 && dir == UP)
	{
		w->player.y += w->player.dy;
		w->player.x += w->player.dx;
	}
	else if (w->player.valid == 0 && dir == DOWN)
	{
		w->player.y -= w->player.dy;
		w->player.x -= w->player.dx;
	}
}
