/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unrotate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:29:32 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/02/02 19:30:07 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stack.h"
#include "vector.h"

//TODO : Determine best way to unrotate
//TODO : Use rotate-or-swap if possible ?
bool	unrotate(t_sub_stack *cur, t_sub_stack *other)
{
	(void)other;
	if (cur->size == cur->stack->size)
		return (0);
	if (vector_append_n(cur->ops, ROTATE_DOWN, cur->rotated))
		return (1);
	return (0);
}
