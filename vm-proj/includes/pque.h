/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pque.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 21:43:51 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/23 17:20:09 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PQUE_H
# define PQUE_H

# include "vector.h"

# define FT_MIN2(x, y) ((x) < (y) ? (x) : (y))

typedef struct	s_pque
{
	void		*data;
	int			priority;
}				t_pque;

void			*push_que(t_vector *vec, void *data, int priority);
t_pque			pop_que(t_vector *vec);

#endif
