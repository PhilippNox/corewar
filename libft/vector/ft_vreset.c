/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vreset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 02:38:08 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/26 13:33:10 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	*ft_vreset(t_vector *v)
{
	if (!v || !v->cont)
		return (NULL);
	ft_bzero(v->cont, v->len);
	v->len = 0;
	v->offset = 0;
	return (v);
}
