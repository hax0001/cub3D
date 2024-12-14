/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gar_co.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:43:43 by nait-bou          #+#    #+#             */
/*   Updated: 2024/12/14 18:12:47 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"


void	ft_free_all(void)
{
	t_list	*head;

	head = g_global->gar_co;
	if (head == NULL)
		free(head);
	ft_lstclear(&head, free);
}

void	*ft_malloc(size_t size)
{
	t_list	*head;
	t_list	*tmp;
	void	*heap_block;

	head = g_global->gar_co;
	heap_block = malloc(size);
	if (!heap_block)
	{
		ft_free_all();
		perror("ft_malloc() failure!");
		exit(EXIT_FAILURE);
	}
	tmp = ft_lstnew(heap_block);
	if (!tmp)
	{
		ft_free_all();
		perror("ft_malloc() failure!");
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(&head, tmp);
	return (heap_block);
}