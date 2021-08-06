/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_texture_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:14:28 by esormune          #+#    #+#             */
/*   Updated: 2021/05/25 15:28:08 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "w3d.h"

/*
** Takes in a line of colour code and saves it first as a string,
** adds the FF, and then into a t_code struct
** that will have the character and the associated uint colour.
*/

static void	w3d_texture_colours(t_textures *t, char *f, int row)
{
	int		i;
	int		j;
	char	colour[8 + 1];

	i = 1;
	j = 0;
	t->codes[row].c = f[i++];
	while (f[i] != '#')
		i++;
	i++;
	while (j < 6)
		colour[j++] = f[i++];
	colour[j++] = 'F';
	colour[j++] = 'F';
	colour[j++] = '\0';
	t->codes[row].colour = ft_atoi_base(colour, 16);
	if (!(t->codes[row].colour))
		die("Malloc error.");
}

void	w3d_texture_codes(t_textures *t, int file, int i)
{
	char	*f;
	int		x;
	int		row;
	int		limit;

	limit = t->amount + 3;
	row = 0;
	while (i < limit)
	{
		x = get_next_line(file, &(f));
		if (x < 0)
			die("Open failure.");
		w3d_texture_colours(t, f, row);
		free(f);
		row++;
		i++;
	}
}

/*
** Goes through the str until the ending '"' char and saves the corresponding
** colour into the unsigned int array.
*/

static int	w3d_texture_parse(t_textures *t, UINT *save, char *str, int j)
{
	int	i;
	int	x;

	i = 1;
	while (str[i] != '"')
	{
		x = 0;
		while (x < t->amount)
		{
			if (str[i] == t->codes[x].c)
			{
				save[j] = t->codes[x].colour;
				j++;
				break ;
			}
			else
				x++;
			if (x >= t->amount)
				die("Texture error.");
		}
		i += t->size;
	}
	return (j);
}

UINT	*w3d_texture_map(t_textures *t, UINT *save, int file)
{
	int		x;
	int		j;
	char	*f;

	j = 0;
	while (1)
	{
		x = get_next_line(file, &(f));
		if (x == 0)
			break ;
		if (x < 0)
			die("Open failure.");
		j = w3d_texture_parse(t, save, f, j);
		free(f);
	}
	return (save);
}
