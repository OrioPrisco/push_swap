/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:21:04 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/25 15:46:23 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_vector	t_vector;
typedef struct s_env	t_env;

typedef struct s_sub_stack
{
	t_vector	*stack;
	t_vector	*ops;
	size_t		size;
	size_t		rotated;
	bool		reversed;
	bool		is_a;
}	t_sub_stack;

//TODO : add ROTATE_OR_SWAP op, as some things can be done with either
//		will make merging ops easier
typedef enum e_stack_ops
{
	ROTATE_UP,
	ROTATE_DOWN,
	PUSH,
	SWAP,
	STOP_COMMIT,
}	t_stack_ops;

bool	sort_stacks(t_sub_stack cur, t_sub_stack other, t_env *env);
bool	translate_stack_ops(t_sub_stack *cur, t_sub_stack *other,
			t_vector *ops);
bool	split_stack(t_sub_stack *cur, t_sub_stack *other, size_t *rotate,
			size_t *pushed);
//if *ops_executes is NULL, execute all operations in *ops
bool	execute_ps_ops(t_vector *a, t_vector *b, t_vector *ops,
			size_t *ops_executed);
bool	execute_ps_ops_env(t_env *env);
bool	unrotate(t_sub_stack *cur, t_sub_stack *other);
#endif
