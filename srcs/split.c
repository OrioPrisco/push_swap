/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:50:17 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/26 15:16:45 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "order.h"
#include "stack.h"
#include "push_swap.h"
#include <stdbool.h>

//TODO: push smallest # of elems ?/ push elems%3 if size is 4 or 5
int	get_median(t_stack_slice *slice)
{
	t_vector	vec;
	int			median;

	vector_copy_n(&vec, slice->stack->data, slice->size);
	vector_sort(&vec);
	median = vec.data[vec.size / 2];
	vector_clear(&vec);
	return (median);
}

static bool	unrotate(t_stack_slice *cur, t_stack_slice *other, size_t rotated)
{
	(void)other;
	if (vector_append(cur->ops, STOP_COMMIT)
		|| vector_append_n(cur->ops, ROTATE_DOWN, rotated))
		return (1);
	return (0);
}

// Do i have to put the stack back into place in all situations ?
// Probably not if the slice is the entire stack. Unsure otherwise
// Maybe with other sorting strategies
//		However can have the next split rotate the slice back into place
//		* Need to store the offset of the slice ? or keep that info somehow
//			Removes the need for no commit, but doesn't hurt to keep around
//TODO : determine which directions is fastest split in
//TODO : figure out whic half (lower or upper) is fastest to split
//TODO : for the last rotate put a ROTATE_OR_SWAP, and let commit fct
//		decide what op to translate into
//			* ISSUE: how do i know how many rotate to push after
//			the STOP_COMMIT ?
//			* maybe make commit look ahead for an REVERSE_ROTATE_OR_SWAP
//			and replace it with the appropriate instruction
//			* Or could add a value after ROTATE_OR_SWAP with special meaning
//			such as the number of instruction to look ahead
bool	split_stack(t_stack_slice *cur, t_stack_slice *other)
{
	int		median;
	size_t	to_push;
	size_t	rotated;
	size_t	i;

	to_push = cur->size / 2;
	median = get_median(cur);
	i = 0;
	rotated = 0;
	while (to_push)
	{
		if (cur->stack->data[i++] < median)
		{
			to_push--;
			if (vector_append(cur->ops, PUSH))
				return (1);
		}
		else
		{
			rotated++;
			if (vector_append(cur->ops, ROTATE_UP))
				return (1);
		}
	}
	return (unrotate(cur, other, rotated));
}
