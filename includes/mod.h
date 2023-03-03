/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:09:30 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/03/03 11:17:11 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_H
# define MOD_H

# include <stddef.h>

typedef struct s_sub_stack	t_sub_stack;

size_t	get_rot(const t_sub_stack *slice);
size_t	minus_mod(size_t a, size_t b, size_t c);

#endif
