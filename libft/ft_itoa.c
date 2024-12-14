/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hax <hax@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:57:19 by nait-bou          #+#    #+#             */
/*   Updated: 2023/11/24 02:51:11 by hax              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	minint(char *s, int *n)
{
	if (*n == -2147483648)
	{
		s[1] = '2';
		*n = -147483648;
	}
}

static int	nlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len += 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*s;
	unsigned int	len;

	len = nlen(n);
	s = (char *)malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	minint(s, &n);
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		s[0] = '-';
		n *= (-1);
	}
	s[len--] = '\0';
	while (n != 0)
	{
		s[len--] = (n % 10) + 48;
		n /= 10;
	}
	return (s);
}
