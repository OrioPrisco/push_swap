/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:44:06 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/23 18:12:22 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# ifndef OUTPUT_DBG
#  define OUTPUT_DBG 0
# endif

# include "vector.h"
# include <stdbool.h>

typedef struct s_env
{
	t_vector	a;
	t_vector	b;
	t_vector	ps_ops;
	size_t		ops_executed;
	size_t		rot_a;
	size_t		rot_b;
}	t_env;

typedef enum e_ps_ops
{
	ERROR,
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
}	t_ps_ops;

bool	init_env(int argc, char **argv, t_env *env);
void	destroy_env(t_env *env);
void	cancel_ops(t_vector *vec, bool stack_ops);
void	merge_ops(t_vector *vec);
#endif
