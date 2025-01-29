/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 23:50:47 by nait-bou          #+#    #+#             */
/*   Updated: 2023/11/23 00:36:45 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*d;
	t_list	*t;

	if (!lst || !del)
		return ;
	d = *lst;
	while (d)
	{
		t = d -> next;
		ft_lstdelone(d, del);
		d = t;
	}
	*lst = NULL;
}
