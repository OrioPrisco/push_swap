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
#include "stack.h"
#include "push_swap.h"
#include "try.h"
#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"
#include "mod.h"
#include "split.h"

//TODO: push smallest # of elems ?/ push elems%3 if size is 4 or 5
//calculates parameters for splitting
//{median, to_push_top, median, to_push_bot}
static bool	get_params(int *params, const t_sub_stack *slice)
{
	t_vector	top;
	t_vector	bot;
	t_vector	all;
	size_t		i;

	if (vector_init(&top), vector_init(&bot), vector_init(&all), 0)
		return (1);
	if ((slice->size > get_rot(slice) && vector_copy_n
			(&top, slice->stack->data, slice->size - get_rot(slice)))
		|| (get_rot(slice) && vector_copy_n(&bot, slice->stack->data
				+ (slice->stack->size - get_rot(slice)), get_rot(slice)))
		|| vector_copy(&all, &top)
		|| vector_append_elems(&all, bot.data, bot.size))
		return (vector_clear(&all), vector_clear(&top), vector_clear(&bot), 1);
	vector_sort(&all);
	ft_bzero(params, 4 * sizeof(*params));
	params[0] = all.data[(all.size / 2)];
	params[2] = all.data[(all.size / 2)];
	i = -1;
	while (++i < top.size)
		((top.data[i] < params[0]) ^ slice->reversed) && params[1]++;
	i = -1;
	while (++i < bot.size)
		((bot.data[i] < params[2]) ^ slice->reversed) && params[3]++;
	return (vector_clear(&all), vector_clear(&top), vector_clear(&bot), 0);
}

static t_f_triable *const	g_strats[] = {
	split_up_down,
	split_down_up,
};

static const t_funcs		g_split_strats = {
	&g_strats[0],
	sizeof(g_strats) / sizeof(*g_strats)
};

//modifies other such that the size and rotated will be accurate
//once ops are translated and executed
//does not clear the instructions vector however
bool	split_stack(t_sub_stack *cur, t_sub_stack *other, void *_)
{
	t_sub_stacks	*best;
	int				params[4];

	(void)_;
	if (get_params(&params[0], cur))
		return (1);
	other->size = 0;
	best = best_strat(cur, other, &g_split_strats, &params[0]);
	if (!best)
		return (1);
	move_substack(cur, &best->cur);
	move_substack(other, &best->other);
	other->reversed = !cur->reversed;
	free(best);
	return (0);
}
