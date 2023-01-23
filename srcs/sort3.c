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

#include "vector.h"
#include "order.h"
#include "push_swap.h"

static	int	sort3_size3(t_vector *ops, t_order3 order)
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

static	int	sort3_size3p(t_vector *ops, t_order3 order)
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

int	sort3(const t_vector *vec, t_vector *stack_ops, int reversed)
{
	t_order3	order;

	order = get_order3(vec, reversed);
	if (vec->size == 3)
		return (sort3_size3(stack_ops, order));
	return (sort3_size3p(stack_ops, order));
}
