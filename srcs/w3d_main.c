/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsankari <jsankari@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:57:18 by jsankari          #+#    #+#             */
/*   Updated: 2021/06/15 15:25:57 by jsankari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

void	w3d_texture_to_renderer(t_wolf *w)
{
	int		*pixels;
	int		pitch;
	int		ret;

	ret = SDL_LockTexture(w->texture, NULL, (void **)&pixels, &pitch);
	if (ret < 0 )
		die("SDL Texture lock failed.");
	ft_memcpy(pixels, w->img, w->img_size);
	SDL_UnlockTexture(w->texture);
	ret = SDL_RenderCopy(w->renderer, w->texture, 0, 0);
	if (ret < 0)
		die("SDL failed to copy map file.");
	SDL_RenderPresent(w->renderer);
}

void	w3d_init_sdl(t_wolf *w)
{
	int	ret;

	ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (ret < 0)
		die("SDL init failure.");
	w->win_ptr = SDL_CreateWindow("Wolf3d", \
SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WID, WIN_HEI, 0);
	if (!(w->win_ptr))
		die("SDL window creation failed.");
	w->renderer = SDL_CreateRenderer(w->win_ptr, -1, 0);
	if (!(w->renderer))
		die("SDL renderer initialisation failed.");
	w->texture = SDL_CreateTexture(w->renderer, \
SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIN_WID, WIN_HEI);
	if (!(w->texture))
		die("SDL texture creation failed.");
}

void	w3d_init_constant_values(t_wolf *w)
{
	w->pp_dist = (WIN_WID * 0.5f) / \
tanf((((float)FOV * 0.5f) * (float)V_PI / 180.0f));
	w->ray.angle = ((float) -FOV / (float)2) * ((float)V_PI / 180.0f);
	w->ray.step = (float)FOV * (float)V_PI / 180.0f / (float)WIN_WID;
	w->pi.north = V_PI * 0.5f;
	w->pi.south = 3.0f * V_PI * 0.5f;
	w->pi.east = 2.0f * V_PI;
	w->pi.west = V_PI;
}

t_wolf	w3d_init(void)
{
	t_wolf	w;

	ft_bzero(&w, sizeof(w));
	w3d_init_sdl(&w);
	w.img_size = WIN_WID * WIN_HEI * 4;
	w.img = (unsigned int *)ft_memalloc(w.img_size);
	if (!(w.img))
		die("SDL image malloc failed");
	w.wall.height = ft_memalloc(WIN_WID * 4);
	w.wall.texture_column = ft_memalloc(WIN_WID * 4);
	w.wall.direction = ft_memalloc(WIN_WID * 4);
	w.bg = ft_calloc((WIN_WID * WIN_HEI), sizeof(unsigned int));
	if (!(w.bg) || !(w.img) || !(w.wall.height)
		|| !(w.wall.texture_column) || !(w.wall.direction))
		die("Malloc failure during initialisation.");
	w3d_draw_background(&w);
	w3d_textures(&w);
	w3d_init_constant_values(&w);
	w.player.dx = cosf(w.player.angle) * 10.0f;
	w.player.dy = sinf(w.player.angle) * 10.0f;
	return (w);
}

int	main(void)
{
	t_wolf	w;
	int		loop;

	loop = 1;
	w = w3d_init();
	w3d_create_map(MAP_PATH, &w);
	w3d_set_player_start(&w);
	while (loop)
	{
		if (SDL_WaitEvent(&w.event) != 0)
		{
			if (w.event.type == SDL_QUIT)
				break ;
			if (w.event.key.keysym.sym)
				loop = w3d_key_events(&w);
		}
		w3d_create_3d_image(&w);
		w3d_texture_to_renderer(&w);
	}
	SDL_Quit();
	return (0);
}
