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
int	get_median(t_sub_stack *slice)
{
	t_vector	vec;
	int			median;

	vector_copy_n(&vec, slice->stack->data, slice->size);
	vector_sort(&vec);
	median = vec.data[(vec.size / 2)];
	vector_clear(&vec);
	return (median);
}

//TODO : determine which directions is fastest split in
//TODO : figure out whic half (lower or upper) is fastest to split
//TODO : for the last rotate put a ROTATE_OR_SWAP, and let commit fct
//		decide what op to translate into
//		/!\unrotating is now left to the sorter, allowing to decouple the split
//		and rotate logic
bool	split_stack(t_sub_stack *cur, t_sub_stack *other, size_t *rotate,
	size_t *pushed)
{
	int		median;
	size_t	to_push;
	size_t	rotated;
	size_t	i;

	(void)other;
	to_push = (cur->size / 2) + (cur->reversed && cur->size % 2);
	median = get_median(cur);
	i = 0;
	rotated = 0;
	if (pushed)
		*pushed = to_push;
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
	if (rotate)
		*rotate = rotated;
	return (0);
}
