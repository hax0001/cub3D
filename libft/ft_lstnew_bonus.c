/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:23:07 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/21 12:43:32 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*d;

	d = (t_list *)malloc(sizeof(t_list));
	if (!d)
		return (NULL);
	d -> content = content;
	d -> next = NULL;
	return (d);
}
