/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:22:36 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/23 18:24:50 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

typedef struct s_vector		t_vector;
typedef struct s_sub_stack	t_sub_stack;

void	print_stack_ops(const t_vector *ops);
void	print_ps_ops(const t_vector *ops);
void	output_ps_ops(const t_vector *ops);
void	print_sub_stacks(const t_sub_stack *a, const t_sub_stack *b);

#endif
