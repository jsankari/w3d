/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsankari <jsankari@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:47:04 by jsankari          #+#    #+#             */
/*   Updated: 2021/03/12 17:47:08 by jsankari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

static t_mir	w3d_mirstruct(void)
{
	t_mir	mir;

	mir.i = 0;
	mir.x = 0;
	mir.b = 0;
	return (mir);
}

int	w3d_map_int_ray(t_wolf *w)
{
	t_mir	mir;
	char	temp[2];

	mir = w3d_mirstruct();
	w->imap = 0;
	w->imap = (int *)malloc(sizeof(int) * (w->maps.mwid * w->maps.mhei));
	if (!(w->imap))
		die("Malloc error in int ray.");
	while (w->map[mir.i] != '\0')
	{
		mir.x = 0;
		ft_memset(temp, 0, 2);
		while (ft_isdigit(w->map[mir.i]) == 1)
		{
			temp[mir.x] = w->map[mir.i];
			mir.i++;
			mir.x++;
		}
		temp[mir.x] = '\0';
		if (temp[0] != '\0')
			w->imap[mir.b++] = ft_atoi(temp);
		while (w->map[mir.i] == ' ' || w->map[mir.i] == '\n')
			mir.i++;
	}
	return (0);
}

void	w3d_create_map(char *map_file, t_wolf *w)
{
	w3d_validate_map(map_file, w);
	w3d_map_reader(map_file, w);
}

static void	w3d_save_map(int fd, t_wolf *w)
{
	char	*temp;
	char	*line;
	int		ret;

	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (ret == 0)
			break ;
		if (w->map == NULL)
			w->map = ft_strnew(0);
		temp = ft_strjoin(w->map, line);
		ft_strdel(&w->map);
		w->map = ft_strjoin(temp, " ");
		ft_strdel(&temp);
		ft_strdel(&line);
		if (ret == -1)
			die("Error reading map file.");
	}
	ft_strdel(&line);
}

int	w3d_map_reader(char *filename, t_wolf *w)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		die("Failed to open map file.");
	w->map = NULL;
	w3d_save_map(fd, w);
	w3d_map_int_ray(w);
	ft_strdel(&w->map);
	close(fd);
	return (0);
}
