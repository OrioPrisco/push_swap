/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:14:22 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/23 18:53:58 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "order.h"
#include "vector.h"

t_order3	get_order3(const t_vector *vec, int reversed)
{
	if ((vec->data[0] > vec->data[1]) ^ reversed)
	{
		if ((vec->data[1] > vec->data[2]) ^ reversed)
			return (CBA);
		if ((vec->data[0] > vec->data[2]) ^ reversed)
			return (CAB);
		return (BAC);
	}
	if ((vec->data[1] < vec->data[2]) ^ reversed)
		return (ABC);
	if ((vec->data[0] < vec->data[2]) ^ reversed)
		return (ACB);
	return (BCA);
}
