/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:52:19 by nait-bou          #+#    #+#             */
/*   Updated: 2023/11/30 17:49:51 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;
	size_t				t;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	t = n;
	if (dest != src)
	{
		if (d > s)
			while (t-- > 0)
				d[t] = s[t];
		else
		{
			while (i < n)
			{
				d[i] = (char)s[i];
				i++;
			}
		}
	}
	return (dest);
}
