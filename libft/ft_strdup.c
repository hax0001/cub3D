/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:42:25 by nait-bou          #+#    #+#             */
/*   Updated: 2023/11/25 06:05:09 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*d;

	len = 0;
	i = 0;
	while (s[i])
	{
		len++;
		i++;
	}
	d = malloc(len + 1);
	if (!d)
		return (NULL);
	ft_memcpy(d, s, len + 1);
	return (d);
}
