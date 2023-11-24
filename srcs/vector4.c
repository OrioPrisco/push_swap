/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orio <47635210+OrioPrisco@users.noreply.g  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:00:08 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/04/03 20:57:25 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vector.h"

bool	vector_is_sorted(t_vector *vector, bool ascending)
{
	size_t	i;

	i = 0;
	while (i + 1 < vector->size)
	{
		if ((vector->data[i] < vector->data[i + 1]) ^ ascending)
			return (0);
		i++;
	}
	return (1);
}
