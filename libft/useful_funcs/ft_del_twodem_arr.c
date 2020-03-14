/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 21:28:55 by vlegros           #+#    #+#             */
/*   Updated: 2019/03/09 17:20:00 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del_twodem_arr(void ***p_arr)
{
	int i;

	if (!p_arr)
		return ;
	i = 0;
	while (((*p_arr) + i) && *((*p_arr) + i))
		free(*((*p_arr) + i++));
	free(*p_arr);
	*p_arr = NULL;
}
