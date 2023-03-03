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
//params : int[2] {median, to_push}
bool	split_up(t_sub_stack *cur, t_sub_stack *other, void *params)
{
	size_t	rotated;
	size_t	i;
	int		median;
	int		to_push;

	median = ((int *)params)[0];
	to_push = ((int *)params)[1];
	i = 0;
	rotated = 0;
	cur->size -= to_push;
	other->size += to_push;
	while (to_push)
	{
		if ((cur->stack->data[i++] < median) ^ cur->reversed)
		{
			if (to_push--, vector_append(cur->ops, PUSH))
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
//params : int[2] {median, to_push}
//FIXME : substraction at the end might be -1
bool	split_down(t_sub_stack *cur, t_sub_stack *other, void *params)
{
	size_t	i;
	int		median;
	int		to_push;
	size_t	rotated;

	median = ((int *)params)[0];
	to_push = ((int *)params)[1];
	i = cur->stack->size;
	cur->size -= to_push;
	other->size += to_push;
	rotated = 0;
	while (to_push)
	{
		if ((cur->stack->data[i-- % cur->stack->size] < median) ^ cur->reversed)
		{
			if ((to_push--, vector_append(cur->ops, PUSH)) || (to_push
					&& (rotated++, vector_append(cur->ops, ROTATE_DOWN))))
				return (1);
		}
		else if (rotated ++, vector_append(cur->ops, ROTATE_DOWN))
			return (1);
	}
	*cur->global_rot = (*cur->global_rot - rotated) % cur->stack->size;
	return (0);
}
