/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:48:59 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/03/03 11:55:48 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_H
# define SPLIT_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_sub_stack	t_sub_stack;

typedef struct s_split_info {
	int		median;
	size_t	push;
}	t_split_info;

bool	split_up(t_sub_stack *cur, t_sub_stack *other, void *params);
bool	split_down(t_sub_stack *cur, t_sub_stack *other, void *params);
bool	split_down_up(t_sub_stack *cur, t_sub_stack *other, void *params_);
bool	split_up_down(t_sub_stack *cur, t_sub_stack *other, void *params_);

#endif
