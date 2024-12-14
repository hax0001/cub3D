/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:04:29 by nait-bou          #+#    #+#             */
/*   Updated: 2023/11/23 02:37:30 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*d;
	size_t	tot;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	tot = nmemb * size;
	d = malloc(tot);
	if (!d)
		return (NULL);
	ft_bzero(d, (nmemb * size));
	return ((void *)d);
}
