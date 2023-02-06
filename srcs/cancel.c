/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cancel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:15:44 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/02/06 15:20:45 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stack.h"
#include "vector.h"

static bool	can_cancel(int a, int b, bool (*f)(int, int))
{
	return (f(a, b) || f(b, a));
}

static bool	can_cancel_ps(int a, int b)
{
	if (a == PA && b == PB)
		return (1);
	if ((a == SA && b == SA) || (a == SB && b == SB) || (a == SS && b == SS))
		return (1);
	if ((a == RA && b == RRA) || (a == RB && b == RRB) || (a == RR && b == RRR))
		return (1);
	return (0);
}

static bool	can_cancel_stack(int a, int b)
{
	if (a == SWAP && b == SWAP)
		return (1);
	if (a == ROTATE_UP && b == ROTATE_DOWN)
		return (1);
	return (0);
}

static void	cancel_ops_impl(t_vector *vec, bool (*f)(int, int))
{
	size_t	i;

	i = 0;
	while (i + 1 < vec->size)
	{
		if (can_cancel(vec->data[i], vec->data[i + 1], f))
		{
			vector_pop_n(vec, i, 2);
			if (i)
				--i;
		}
		else
			i++;
	}
}

void	cancel_ops(t_vector *vec, bool stack_ops)
{
	if (stack_ops)
		return (cancel_ops_impl(vec, can_cancel_stack));
	else
		return (cancel_ops_impl(vec, can_cancel_ps));
}
