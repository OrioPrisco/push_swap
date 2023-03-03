/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:45:50 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/03/03 11:49:57 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "stack.h"
#include "split.h"
#include <stdbool.h>
#include "mod.h"

//TODO : for the last rotate put a ROTATE_OR_SWAP, and let commit fct
//		decide what op to translate into
//		/!\unrotating is now left to the sorter, allowing to decouple the split
//		and rotate logic
bool	split_up(t_sub_stack *cur, t_sub_stack *other, void *params_)
{
	size_t			rotated;
	size_t			i;
	t_split_info	params;

	params = *(t_split_info *)params_;
	i = 0;
	rotated = 0;
	cur->size -= params.push;
	other->size += params.push;
	while (params.push)
	{
		if ((cur->stack->data[i++] < params.median) ^ cur->reversed)
		{
			if (params.push--, vector_append(cur->ops, PUSH))
				return (1);
		}
		else if (rotated++, vector_append(cur->ops, ROTATE_UP))
			return (1);
	}
	*cur->global_rot = (*cur->global_rot + rotated) % cur->stack->size;
	return (0);
}

//TODO : on reverse rotate, if the next elem also is to be pushed,
//		push the smallest first, by maybe delaying the push
//FIXME : substraction at the end might be -1
bool	split_down(t_sub_stack *cur, t_sub_stack *other, void *params_)
{
	size_t			i;
	size_t			rotated;
	t_split_info	params;

	params = *(t_split_info *)params_;
	i = cur->stack->size;
	cur->size -= params.push;
	other->size += params.push;
	rotated = 0;
	while (params.push)
	{
		if ((cur->stack->data[i-- % cur->stack->size] < params.median)
			^ cur->reversed)
		{
			if ((params.push--, vector_append(cur->ops, PUSH)) || (params.push
					&& (rotated++, vector_append(cur->ops, ROTATE_DOWN))))
				return (1);
		}
		else if (rotated ++, vector_append(cur->ops, ROTATE_DOWN))
			return (1);
	}
	*cur->global_rot = (*cur->global_rot - rotated) % cur->stack->size;
	return (0);
}
