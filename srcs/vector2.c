/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:25:51 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/20 18:06:35 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

t_vector_data	vector_pop(t_vector *vector, size_t index)
{
	t_vector_data	data;

	data = vector->data[index];
	ft_memmove(vector->data + index, vector->data + index + 1,
		(vector->size - index - 1) * sizeof(*vector->data));
	vector->size--;
	return (data);
}

int	vector_insert(t_vector *vector, size_t index, t_vector_data data)
{
	if (vector->malloced_size == 0)
		if (vector_allocate(vector, DEFAULT_VECTOR_SIZE))
			return (1);
	if (vector->size == vector->malloced_size)
		if (vector_grow(vector))
			return (1);
	ft_memmove(vector->data + index + 1, vector->data + index,
		(vector->size - index) * sizeof(*vector->data));
	vector->data[index] = data;
	vector->size++;
	return (0);
}
