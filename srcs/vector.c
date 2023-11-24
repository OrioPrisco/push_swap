/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:09:19 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/20 17:38:27 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

t_vector	*vector_init(t_vector *vector)
{
	ft_bzero(vector, sizeof(*vector));
	return (vector);
}

bool	vector_allocate(t_vector *vector, size_t size)
{
	if (size == 0)
		size = 1;
	vector->size = 0;
	vector->data = malloc(size * sizeof(*vector->data));
	if (!vector->data)
		return (1);
	vector->malloced_size = size;
	return (0);
}

bool	vector_append(t_vector *vector, t_vector_data data)
{
	if (vector_ensure_capacity(vector, 1))
		return (1);
	vector->data[vector->size] = data;
	vector->size++;
	return (0);
}

t_vector	*vector_clear(t_vector *vector)
{
	if (!vector)
		return (NULL);
	free(vector->data);
	vector->data = 0;
	vector->size = 0;
	vector->malloced_size = 0;
	return (vector);
}

bool	vector_ensure_capacity(t_vector *vector, size_t size)
{
	t_vector_data	*new_data;
	size_t			new_size;

	if (vector->malloced_size == 0 && size < DEFAULT_VECTOR_SIZE)
		return (vector_allocate(vector, DEFAULT_VECTOR_SIZE));
	if (vector->malloced_size == 0)
		return (vector_allocate(vector, size));
	if (vector->size + size < vector->malloced_size)
		return (0);
	new_size = vector->malloced_size / sizeof(*vector->data) * 2;
	while (vector->size + size > new_size)
		new_size *= 2;
	new_data = malloc(new_size * sizeof(*vector->data));
	if (!new_data)
		return (1);
	ft_memcpy(new_data, vector->data, vector->size * sizeof(*vector->data));
	free(vector->data);
	vector->data = new_data;
	vector->malloced_size *= 2;
	return (0);
}
