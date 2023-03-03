/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_stacks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:22:26 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/03/03 18:24:15 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "try.h"
#include "vector.h"
#include "libft.h"

bool	copy_sub_stack(t_sub_stack *dest, const t_sub_stack *src)
{
	*dest = *src;
	dest->stack = malloc(sizeof(*dest->stack));
	dest->ops = malloc(sizeof(*dest->ops));
	dest->global_rot = malloc(sizeof(*dest->global_rot));
	if (!dest->stack || !dest->ops || !dest->global_rot)
	{
		free(dest->stack);
		free(dest->ops);
		free(dest->global_rot);
		return (1);
	}
	*dest->global_rot = *src->global_rot;
	dest->local_rot = src->local_rot;
	if (vector_copy(dest->stack, src->stack)
		|| vector_copy(dest->ops, src->ops))
	{
		free(vector_clear(dest->stack));
		free(vector_clear(dest->ops));
		return (1);
	}
	return (0);
}

t_sub_stacks	*destroy_sub_stacks(t_sub_stacks *stacks)
{
	free(vector_clear(stacks->cur.stack));
	free(vector_clear(stacks->cur.ops));
	free(vector_clear(stacks->other.stack));
	free(vector_clear(stacks->other.ops));
	free(stacks->cur.global_rot);
	free(stacks->other.global_rot);
	ft_bzero(stacks, sizeof(*stacks));
	return (stacks);
}

t_sub_stack	*move_substack(t_sub_stack *dest, t_sub_stack *src)
{
	free(vector_move(dest->ops, src->ops));
	free(vector_move(dest->stack, src->stack));
	dest->size = src->size;
	*dest->global_rot = *src->global_rot;
	free(src->global_rot);
	dest->local_rot = src->local_rot;
	dest->reversed = src->reversed;
	dest->is_a = src->is_a;
	ft_bzero(src, sizeof(*src));
	return (dest);
}
