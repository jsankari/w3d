/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:54:02 by esormune          #+#    #+#             */
/*   Updated: 2021/05/17 13:05:16 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t oldsize, size_t newsize)
{
	char	*new;

	if ((!newsize && ptr))
	{
		new = (char *)malloc(1);
		if (!new)
			return (NULL);
		ft_memdel(&ptr);
		return (new);
	}
	if (newsize <= oldsize)
		return (ptr);
	new = ft_calloc(newsize, sizeof(char));
	if (!new)
		return (NULL);
	ft_memcpy(new, ptr, oldsize);
	if (ptr)
		ft_memdel(&ptr);
	return (new);
}
