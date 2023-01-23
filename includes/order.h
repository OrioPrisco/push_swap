/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:12:32 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/23 15:30:13 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ORDER_H
# define ORDER_H

typedef struct s_vector	t_vector;

typedef enum e_order3
{
	ABC,
	ACB,
	BAC,
	BCA,
	CAB,
	CBA,
}	t_order3;

t_order3	get_order3(const t_vector *vec, int reversed);

#endif
