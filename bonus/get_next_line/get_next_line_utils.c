/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:56:12 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/21 12:37:27 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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
	d = ft_malloc(len + 1);
	if (!d)
		return (NULL);
	ft_memmove(d, s, len + 1);
	return (d);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	stot_len;
	char	*str;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen(s2);
	stot_len = s1_len + s2_len + 1;
	str = ft_malloc(sizeof(char) * stot_len);
	if (!str)
		return (0);
	ft_memmove(str, s1, s1_len);
	ft_memmove(str + s1_len, s2, s2_len);
	str[stot_len - 1] = '\0';
	return (str);
}

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
