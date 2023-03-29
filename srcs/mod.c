/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:01:45 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/03/03 11:17:42 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod.h"
#include "stack.h"
#include "vector.h"

size_t	minus_mod(size_t a, size_t b, size_t c)
{
	if (b <= a)
		return ((a - b) % c);
	return ((a + c - (b - c)) % c);
}

size_t	get_rot(const t_sub_stack *slice)
{
	if (slice->stack->size == slice->size)
		return (0);
	return (
		minus_mod(*slice->global_rot, slice->local_rot, slice->stack->size));
}

size_t	min_st(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

size_t	sub_stack_start(const t_sub_stack *slice)
{
	if (slice->stack->size == 0)
		return (0);
	return (minus_mod
		(slice->stack->size, get_rot(slice), slice->stack->size));
}

size_t	sub_stack_end(const t_sub_stack *slice)
{
	if (slice->stack->size == 0)
		return (0);
	return ((sub_stack_start(slice) + slice->size) % slice->stack->size);
}
