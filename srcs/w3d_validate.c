/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:01:45 by esormune          #+#    #+#             */
/*   Updated: 2021/06/14 14:32:52 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

int	w3d_validate_line(char *line, t_wolf *w)
{
	int		i;
	int		spawn;
	size_t	len;

	i = 0;
	spawn = 0;
	len = ft_strlen(line);
	if (len >= 200)
		return (2);
	if (w->maps.mwid == 0)
		w->maps.mwid = ft_countstring(line, ' ');
	if (ft_countstring(line, ' ') != w->maps.mwid)
		die("Invalid map: lines are not equal.");
	while (line[i] != '\0')
	{
		if ((line[i] < '0' || line[i] > '2') && line[i] != ' ')
			die("Map is not correct format.");
		if ((line[i] >= '0' && line[i] <= '2') && ft_isdigit(line[i + 1]) == 1)
			die("Map is not correct format.");
		if (line[i] == '2')
			spawn++;
		i++;
	}
	return (spawn);
}

int	w3d_validate_map(char *filename, t_wolf *w)
{
	int		fd;
	char	*line;
	int		ret;
	int		spawn;

	spawn = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		die("Failed to open map file.");
	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret == 0)
			break ;
		if (ret == -1)
			die("Error reading map file.");
		spawn += w3d_validate_line(line, w);
		ft_strdel(&line);
		w->maps.mhei++;
	}
	if ((ret == 0 && w->maps.mhei == 0) || spawn != 1)
		die("Invalid map.");
	ft_strdel(&line);
	close(fd);
	return (0);
}
