/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gar_co.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:43:43 by nait-bou          #+#    #+#             */
/*   Updated: 2024/12/13 14:22:59 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

static t_mlx    **get_heap(void)
{
    static t_mlx    *heap;
    return (&heap);
}

void	ft_free_all(void)
{
	t_list	**head;

	head = get_heap();
	if (head == NULL)
		free(head);
	ft_lstclear(head, free);
}

void	*ft_malloc(size_t size)
{
	t_list	**head;
	t_list	*tmp;
	void	*heap_block;

	head = get_heap();
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
	ft_lstadd_back(head, tmp);
	return (heap_block);
}