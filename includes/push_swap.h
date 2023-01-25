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

# include "vector.h"

typedef struct s_env
{
	t_vector	a;
	t_vector	b;
	t_vector	ps_ops;
}	t_env;

typedef enum e_ps_ops
{
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

int		init_env(int argc, char **argv, t_env *env);
void	destroy_env(t_env *env);
#endif
