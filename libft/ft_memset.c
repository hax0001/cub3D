/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:06:39 by nait-bou          #+#    #+#             */
/*   Updated: 2023/11/30 17:49:41 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*v;
	size_t			i;

	i = 0;
	v = (unsigned char *)s;
	while (i < n)
	{
		v[i] = (unsigned char)c;
		i++;
	}
	return ((void *)v);
}
