/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:27:39 by ugerkens          #+#    #+#             */
/*   Updated: 2024/04/17 15:27:43 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_status	calloc_s(void **pointer, size_t size, t_simulation *sim)
{
	*pointer = malloc(size);
	if (!*pointer)
		return (ERROR_ALLOCATION);
	if (track_alloc((void *)*pointer, sim) != SUCCESS)
		return (ERROR_ALLOCATION);
	memset(*pointer, 0, size);
	return (SUCCESS);
}

t_status	track_alloc(void *pointer, t_simulation *sim)
{
	t_list	*new_node;

	new_node = ft_lstnew(pointer);
	if (!new_node)
	{
		free(pointer);
		return (ERROR_ALLOCATION);
	}
	ft_lstadd_front(&sim->allocated_pointers, new_node);
	return (SUCCESS);
}
