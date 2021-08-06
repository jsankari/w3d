/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:22:24 by esormune          #+#    #+#             */
/*   Updated: 2021/05/25 15:24:02 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

/*
** Returns the allocated memory for the unsigned int array
** that will hold the texture. Also saves into the t_textures struct,
** that contains all the textures, the size of the t_code array
** and frees it from its previous saved colour codes. Starts the count
** at 1, which is initialised as 'i' in function call.
*/

static unsigned int	*w3d_get_stats(t_textures *t, char *str, int i)
{
	int				x;
	int				y;
	unsigned int	*ret;

	if (t->codes != NULL)
		free(t->codes);
	x = ft_atoi(&str[i]);
	i += ft_numlength(x);
	while (!ft_isdigit(str[i]))
		i++;
	y = ft_atoi(&str[i]);
	i += ft_numlength(y);
	while (!ft_isdigit(str[i]))
		i++;
	t->amount = ft_atoi(&str[i]);
	i += ft_numlength(t->amount);
	t->size = ft_atoi(&str[i]);
	if (t->size != 1)
		die("Texture file error.");
	t->codes = ft_calloc(t->amount, sizeof(t_codes));
	ret = ft_calloc((x * y), sizeof(unsigned int));
	if (!ret || !(t->codes))
		die("Malloc error.");
	return (ret);
}

/*
** In the correct xpm file, the stats will be on row 3. First it
** gets to that row, then extracts the necessar information from it,
** including the size of the image and amount of colour codes.
** Then, the parser reads the specified amount of colour codes lines
** and sends them to be saved into t->codes. Then it parses the rest of
** the code to an uint array of colours. Is split in two functions.
*/

UINT	*w3d_texture_extract(t_textures *t, int file)
{
	int		x;
	int		i;
	char	*f;
	UINT	*save;

	i = 0;
	while (i < 3)
	{
		x = get_next_line(file, &(f));
		if (x < 0)
			die("Open failure.");
		else if (x == 0)
			die("Texture failure.");
		if (i != 2)
			free(f);
		i++;
	}
	save = w3d_get_stats(t, f, 1);
	free(f);
	w3d_texture_codes(t, file, i);
	w3d_texture_map(t, save, file);
	return (save);
}

void	w3d_textures(t_wolf *w)
{
	int	file;
	int	i;

	i = 0;
	file = open (N_TXTR, O_RDONLY);
	if (file < 0)
		return (die("File open failure."));
	w->textures.north = w3d_texture_extract(&(w->textures), file);
	close (file);
	file = open (E_TXTR, O_RDONLY);
	if (file < 0)
		return (die("File open failure."));
	w->textures.east = w3d_texture_extract(&(w->textures), file);
	close (file);
	file = open (S_TXTR, O_RDONLY);
	if (file < 0)
		return (die("File open failure."));
	w->textures.south = w3d_texture_extract(&(w->textures), file);
	close (file);
	file = open (W_TXTR, O_RDONLY);
	if (file < 0)
		return (die("File open failure."));
	w->textures.west = w3d_texture_extract(&(w->textures), file);
	close (file);
}
