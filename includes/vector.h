/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:09:50 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/20 17:02:39 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stddef.h>
# define DEFAULT_VECTOR_SIZE 10
//for now only grows, and never shrinks
typedef int	t_vector_data;

typedef struct s_vector {
	size_t			size;
	size_t			malloced_size;
	t_vector_data	*data;
}	t_vector;

void			vector_init(t_vector *vector);
int				vector_allocate(t_vector *vector, size_t size);
int				vector_append(t_vector *vector, t_vector_data data);
void			vector_clear(t_vector *vector);
int				vector_maybe_grow(t_vector *vector);
t_vector_data	vector_pop(t_vector *vector, size_t index);
int				vector_insert(t_vector *vector, size_t index,
					t_vector_data data);
int				vector_copy(t_vector *des, t_vector *src);
void			vector_sort(t_vector *vector);

#endif
