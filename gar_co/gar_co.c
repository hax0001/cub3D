/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gar_co.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:43:43 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/26 18:48:30 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

typedef struct Allocation {
    void *ptr;
    struct Allocation *next;
} Allocation;

static Allocation *allocations = NULL;

// Function to allocate memory and keep track of it
void *ft_malloc(size_t size) 
{
    void *ptr;
    Allocation *new_alloc;

    ptr = malloc(size);
    if (!ptr)
    {
        ft_putstr_fd("Error\nMemory allocation failed\n", 2);
        exit(EXIT_FAILURE);
    }
    new_alloc = (Allocation *)malloc(sizeof(Allocation));
    if (!new_alloc) {
        ft_putstr_fd("Errot\nMemory allocation failed\n",2);
        exit(EXIT_FAILURE);
    }
    new_alloc->ptr = ptr;
    new_alloc->next = allocations;
    allocations = new_alloc;
    return ptr;
}

// Function to free all tracked allocations
void    ft_free_all()
{
    Allocation *current;
    Allocation *next;

    current = allocations;
    while (current)
    {
        next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    allocations = NULL;
}

// #include "../Includes/cub3d.h"

t_global **get_heap(void)
{
    static t_global *global;

    return (&global);
}

// void ft_free_block(void *block)
// {
//     free(block);
// }

// void ft_free_all(void)
// {
//     t_global *global = *get_heap();
//     if (!global)
//         return;

//     // Free the garbage collector list and its contents
//     if (global->gar_co)
//     {
//         ft_lstclear(&global->gar_co, free); // Frees all memory in gar_co
//         global->gar_co = NULL; // Avoid dangling pointers
//     }

//     // Free other dynamically allocated resources if they exist
//     if (global->data)
//     {
//         free(global->data);
//         global->data = NULL; // Avoid dangling pointer
//     }

//     if (global->ray)
//     {
//         free(global->ray);
//         global->ray = NULL; // Avoid dangling pointer
//     }

//     if (global->player)
//     {
//         free(global->player);
//         global->player = NULL; // Avoid dangling pointer
//     }

//     // Free the global structure itself
//     free(global);
//     *get_heap() = NULL; // Reset static pointer to NULL
// }


// void *ft_malloc(size_t size)
// {
//     t_global *global;
//     t_list   *new_block;
//     void     *heap_block;

//     // Ensure global is initialized (only the first time)
//     global = *get_heap();
//     if (!global)
//     {
//         global = malloc(sizeof(t_global));
//         if (!global)
//             ft_error(ERR_MEMORY_ALLOCATION);
        
//         ft_memset(global, 0, sizeof(t_global));  // Initialize the global structure
//         *get_heap() = global;  // Set the global pointer
//     }

//     // Allocate memory block
//     heap_block = malloc(size);
//     if (!heap_block)
//         ft_error(ERR_MEMORY_ALLOCATION);

//     // Add to garbage collector list
//     new_block = ft_lstnew(heap_block);
//     if (!new_block)
//     {
//         free(heap_block);  // Free memory in case of failure
//         ft_error(ERR_MEMORY_ALLOCATION);
//     }

//     // Add the new block to the garbage collector list
//     ft_lstadd_back(&global->gar_co, new_block);
//     return heap_block;
// }


// // Optional: Add a function to free specific allocations
// void ft_free(void *ptr)
// {
//     t_global *global = *get_heap();
//     t_list *current = global->gar_co;
//     t_list *prev = NULL;

//     while (current)
//     {
//         if (current->content == ptr)
//         {
//             // Remove from garbage collector list
//             if (prev)
//                 prev->next = current->next;
//             else
//                 global->gar_co = current->next;

//             // Free the memory
//             free(ptr);
//             free(current);
//             return;
//         }
//         prev = current;
//         current = current->next;
//     }
// }
