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
	if (vector_maybe_grow(vector))
		return (0);
	ft_memmove(vector->data + index + 1, vector->data + index,
		(vector->size - index) * sizeof(*vector->data));
	vector->data[index] = data;
	vector->size++;
	return (0);
}

void	vector_sort(t_vector *vector)
{
	size_t			i;
	size_t			j;
	t_vector_data	temp;

	i = 0;
	while (i < vector->size)
	{
		j = i + 1;
		while (j < vector->size)
		{
			if (vector->data[i] > vector->data[j])
			{
				temp = *(vector->data + i);
				*(vector->data + i) = *(vector->data + j);
				*(vector->data + j) = temp;
			}
			j++;
		}
		i++;
	}
}

int	vector_copy(t_vector *dest, t_vector *src)
{
	return (vector_copy_n(dest, src->data, src->size));
}

int	vector_copy_n(t_vector *dest, t_vector_data *src, size_t n)
{
	dest->data = malloc(n * sizeof(*src));
	if (!dest->data)
		return (1);
	ft_memcpy(dest->data, src, n * sizeof(*src));
	dest->size = n;
	dest->malloced_size = n;
	return (0);
}
