/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:15:44 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/02/06 19:27:51 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stack.h"
#include "vector.h"

static int	merge_ps(int a, int b)
{
	if (a == SA && b == SB)
		return (SS);
	if ((a == RA && b == RB))
		return (RR);
	if ((a == RRA && b == RRB))
		return (RRR);
	return (-1);
}

static int	merge(int a, int b)
{
	int	res;

	res = merge_ps(a, b);
	if (res != -1)
		return (res);
	return (merge_ps(b, a));
}

void	merge_ops(t_vector *vec)
{
	size_t	i;
	int		res;

	i = 0;
	while (i + 1 < vec->size)
	{
		res = merge(vec->data[i], vec->data[i + 1]);
		if (res != -1)
		{
			vector_pop_n(vec, i, 1);
			vec->data[i] = res;
		}
		else
			i++;
	}
}
