/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:56:21 by nait-bou          #+#    #+#             */
/*   Updated: 2023/11/20 00:42:16 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	t;

	t = (char)c;
	while (*s)
	{
		if (*s == t)
			return ((char *)s);
		s++;
	}
	if (t == '\0')
		return ((char *)s);
	else
		return (NULL);
}
