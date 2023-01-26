/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:37:12 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/26 12:56:38 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

//TODO : make a better implementation
bool	vector_append_n(t_vector *vector, t_vector_data data, size_t n)
{
	while (n--)
		if (vector_append(vector, data))
			return (1);
	return (0);
}

void	vector_pop_n(t_vector *vector, size_t index, size_t n)
{
	ft_memmove(vector->data + index, vector->data + index + n,
		(vector->size - index - n) * sizeof(*vector->data));
	vector->size -= n;
}
