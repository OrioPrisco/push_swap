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
# include <stdbool.h>
# define DEFAULT_VECTOR_SIZE 10
//for now only grows, and never shrinks
typedef int	t_vector_data;

typedef struct s_vector {
	size_t			size;
	size_t			malloced_size;
	t_vector_data	*data;
}	t_vector;

//All Functions returning bool will return 1 on allocation error
//    or 0 on success. They will leave the vector in a state that can be
//    cleared with vector_clear

void			vector_init(t_vector *vector);
bool			vector_allocate(t_vector *vector, size_t size);
bool			vector_append(t_vector *vector, t_vector_data data);
//Frees all the memory inside the vector and resets the vector back to all 0s
//Does not free the t_vector *
void			vector_clear(t_vector *vector);
bool			vector_maybe_grow(t_vector *vector);
t_vector_data	vector_pop(t_vector *vector, size_t index);
bool			vector_insert(t_vector *vector, size_t index,
					t_vector_data data);
//Does not clear the vector, But Initializes it
bool			vector_copy(t_vector *des, const t_vector *src);
//Does not clear the vector, But Initializes it
bool			vector_copy_n(t_vector *dest, const t_vector_data *src,
					size_t n);
void			vector_sort(t_vector *vector);

#endif
