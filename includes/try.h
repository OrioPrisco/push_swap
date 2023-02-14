/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:18:27 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/02/14 17:42:35 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRY_H
# define TRY_H

typedef struct s_sub_stack	t_sub_stack;
typedef bool				t_f_triable (t_sub_stack *, t_sub_stack *, void *);

typedef struct s_sub_stacks
{
	t_sub_stack	cur;
	t_sub_stack	other;
}	t_sub_stacks;

typedef struct s_funcs
{
	t_f_triable *const	*strats;
	size_t				size;
}	t_funcs;

bool			copy_sub_stack(t_sub_stack *dest, const t_sub_stack *src);
t_sub_stacks	*destroy_sub_stacks(t_sub_stacks *stacks);
t_sub_stack		*move_substack(t_sub_stack *dest, t_sub_stack *src);
t_sub_stacks	*try_strat(const t_sub_stack *cur, const t_sub_stack *other,
					t_f_triable *strats, void *params);
t_sub_stacks	*best_strat(const t_sub_stack *cur, const t_sub_stack *other,
					const t_funcs *strats, void *param);
#endif
