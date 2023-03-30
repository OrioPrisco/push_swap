/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:14:22 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/23 18:53:58 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "order.h"
#include "vector.h"
#include "stack.h"
#include "mod.h"

t_order3	get_order3(const t_sub_stack *slice)
{
	size_t			rot;
	size_t			first;
	size_t			second;
	size_t			third;
	const t_vector	*vec;

	rot = get_rot(slice);
	first = sub_stack_start(slice);
	second = (first + 1) % slice->stack->size;
	third = (second + 1) % slice->stack->size;
	vec = slice->stack;
	if ((vec->data[first] > vec->data[second]) ^ slice->reversed)
	{
		if ((vec->data[second] > vec->data[third]) ^ slice->reversed)
			return (CBA);
		if ((vec->data[first] > vec->data[third]) ^ slice->reversed)
			return (CAB);
		return (BAC);
	}
	if ((vec->data[second] < vec->data[third]) ^ slice->reversed)
		return (ABC);
	if ((vec->data[first] < vec->data[third]) ^ slice->reversed)
		return (ACB);
	return (BCA);
}
