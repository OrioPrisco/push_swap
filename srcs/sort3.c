/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:50:17 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/23 18:55:08 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"
#include "vector.h"
#include "order.h"
#include "push_swap.h"
#include "stack.h"
#include "mod.h"

static bool	sort3_size3(t_vector *ops, t_order3 order)
{
	if (order == ABC)
		return (0);
	if (order == ACB)
		return (vector_append(ops, ROTATE_DOWN) || sort3_size3(ops, BAC));
	if (order == BAC)
		return (vector_append(ops, SWAP));
	if (order == BCA)
		return (vector_append(ops, ROTATE_DOWN));
	if (order == CAB)
		return (vector_append(ops, ROTATE_UP));
	return (vector_append(ops, SWAP) || sort3_size3(ops, BCA));
}

//TODO: when sub stack shift is implemented, do no generate the last rotate
//instructions, defer them instead ? Might not have an impact actually
static bool	sort3_size3p(t_vector *ops, t_order3 order)
{
	if (order == ABC)
		return (0);
	if (order == ACB)
		return (vector_append(ops, ROTATE_UP) || vector_append(ops, SWAP)
			|| vector_append(ops, ROTATE_DOWN));
	if (order == BAC)
		return (vector_append(ops, SWAP));
	if (order == BCA)
		return (vector_append(ops, ROTATE_UP) || vector_append(ops, SWAP)
			|| vector_append(ops, ROTATE_DOWN) || vector_append(ops, SWAP));
	if (order == CAB)
		return (vector_append(ops, SWAP) || sort3_size3p(ops, ACB));
	return (vector_append(ops, SWAP) || sort3_size3p(ops, BCA));
}

bool	sort3(t_sub_stack *slice, t_sub_stack *other, void *_)
{
	t_order3	order;
	size_t		rot;
	size_t		first;
	size_t		second;

	(void)_;
	if (slice->size <= 1)
		return (0);
	if (slice->size == 2)
	{
		rot = get_rot(slice);
		first = minus_mod(0, rot, slice->stack->size);
		second = minus_mod(1, rot, slice->stack->size);
		if ((slice->stack->data[first] > slice->stack->data[second])
			^ slice->reversed)
			return (unrotate(slice, other, NULL)
				|| vector_append(slice->ops, SWAP));
		return (0);
	}
	order = get_order3(slice);
	if (slice->stack->size == 3)
		return (unrotate(slice, other, NULL) || sort3_size3(slice->ops, order));
	return (unrotate(slice, other, NULL) || sort3_size3p(slice->ops, order));
}
