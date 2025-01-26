/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gar_co.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:43:43 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/26 19:12:03 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

static Allocation	*g_allocations = NULL;

void	*ft_malloc(size_t size)
{
	void		*ptr;
	Allocation	*new_alloc;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	new_alloc = (Allocation *)malloc(sizeof(Allocation));
	if (!new_alloc)
	{
		ft_putstr_fd("Errot\nMemory allocation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	new_alloc->ptr = ptr;
	new_alloc->next = g_allocations;
	g_allocations = new_alloc;
	return (ptr);
}

void	ft_free_all(void)
{
	Allocation	*current;
	Allocation	*next;

	current = g_allocations;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	g_allocations = NULL;
}

t_global	**get_heap(void)
{
	static t_global	*global;

	return (&global);
}
