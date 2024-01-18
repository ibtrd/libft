/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 00:07:10 by ibertran          #+#    #+#             */
/*   Updated: 2024/01/18 04:02:46 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void	*ft_vector_get(t_vector *v, size_t index)
{
	void	*ptr;

	if (!v || index >= v->total)
		return (NULL);
	ptr = v->items + index * v->item_size;
	return (ptr);
}
