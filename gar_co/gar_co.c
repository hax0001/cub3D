/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gar_co.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:43:43 by nait-bou          #+#    #+#             */
/*   Updated: 2024/12/18 20:23:06 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

t_global **get_heap(void)
{
	static t_global *global;

	return (&global);
}

void	ft_free_all(void)

{
	t_global	*global;
	t_list		*head;

	global = *get_heap();
	head = global->gar_co;
	if (head == NULL)
		free(head);
	ft_lstclear(&head, free);
}

void	*ft_malloc(size_t size)
{
	t_global	*global;
	t_list		*head;
	t_list		*tmp;
	void		*heap_block;


	global = *get_heap();
	head = global->gar_co;
	heap_block = malloc(size);
	if (!heap_block)
		ft_error(ERR_MEMORY_ALLOCATION);
	tmp = ft_lstnew(heap_block);
	if (!tmp)
		ft_error(ERR_MEMORY_ALLOCATION);
	ft_lstadd_back(&head, tmp);
	return (heap_block);
}