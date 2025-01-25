/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:50:32 by nait-bou          #+#    #+#             */
/*   Updated: 2023/11/20 00:47:10 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*t;
	char		r;

	t = NULL;
	r = (char)c;
	while (*s)
	{
		if (*s == r)
			t = s;
		s++;
	}
	if (r == '\0')
		t = s;
	if (t == NULL)
		return (NULL);
	return ((char *)t);
}
