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
static int	get_median(t_sub_stack *slice)
{
	t_vector	vec;
	int			median;

	vector_copy_n(&vec, slice->stack->data, slice->size);
	vector_sort(&vec);
	median = vec.data[(vec.size / 2)];
	vector_clear(&vec);
	return (median);
}

//TODO : for the last rotate put a ROTATE_OR_SWAP, and let commit fct
//		decide what op to translate into
//		/!\unrotating is now left to the sorter, allowing to decouple the split
//		and rotate logic
static bool	split_up(t_sub_stack *cur, size_t *rotate, int median,
	size_t to_push)
{
	size_t	rotated;
	size_t	i;

	i = 0;
	rotated = 0;
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

//TODO : on reverse rotate, if the next elem also is to be pushed,
//		push the smallest first, by maybe delaying the push
static bool	split_down(t_sub_stack *cur, size_t *rotate, int median,
	size_t to_push)
{
	size_t	rotated;
	size_t	i;

	i = 0;
	rotated = 0;
	while (to_push)
	{
		if ((cur->stack->data[i] < median) ^ cur->reversed)
		{
			if ((rotated++, to_push--, vector_append(cur->ops, PUSH))
				|| (to_push && vector_append(cur->ops, ROTATE_DOWN)))
				return (1);
		}
		else if (rotated++, vector_append(cur->ops, ROTATE_DOWN))
			return (1);
		if (i-- == 0)
			i = cur->stack->size - 1;
	}
	if (rotate)
		*rotate = rotated;
	return (0);
}

//TODO don't use pushed for storage, might be null ?
// or make it a requirement to not be null
bool	split_stack(t_sub_stack *cur, t_sub_stack *other, size_t *rotated,
	size_t *pushed)
{
	t_vector	ops_up;
	t_vector	ops_down;
	int			median;
	size_t		rotated_d;
	t_sub_stack	cpy;

	(void)other;
	*pushed = (cur->size / 2) + (cur->reversed && cur->size % 2);
	median = get_median(cur);
	cpy = (t_sub_stack)
	{cur->stack, vector_init(&ops_up), cur->size, cur->rotated, cur->reversed};
	if (split_up(&cpy, rotated, median, *pushed))
		return (vector_clear((vector_clear(&ops_down), &ops_up)), 1);
	cpy = (t_sub_stack){cur->stack,
		vector_init(&ops_down), cur->size, cur->rotated, cur->reversed};
	if (split_down(&cpy, &rotated_d, median, *pushed))
		return (vector_clear((vector_clear(&ops_down), &ops_up)), 1);
	if (ops_up.size > ops_down.size)
		if (vector_append_elems(cur->ops, ops_down.data, ops_down.size))
			return (vector_clear((vector_clear(&ops_down), &ops_up)), 1);
	if (ops_up.size > ops_down.size)
		rotated && (*rotated = rotated_d);
	else if (vector_append_elems(cur->ops, ops_up.data, ops_up.size))
		return (vector_clear((vector_clear(&ops_down), &ops_up)), 1);
	return (vector_clear((vector_clear(&ops_down), &ops_up)), 0);
}
