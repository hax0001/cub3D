/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:06:21 by nait-bou          #+#    #+#             */
/*   Updated: 2023/11/18 04:56:46 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*v;
	unsigned char	t;
	size_t			i;

	v = (unsigned char *)s;
	t = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*v == t)
		{
			return (v);
		}
		i++;
		v++;
	}
	v = NULL;
	return (v);
}
