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

typedef struct s_vector	t_vector;

typedef struct s_stack_slice
{
	t_vector	*stack;
	t_vector	*ops;
	size_t		size;
	bool		reversed;
}	t_stack_slice;

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

#endif
