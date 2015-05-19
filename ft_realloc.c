/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:43:16 by cfriot            #+#    #+#             */
/*   Updated: 2015/03/23 15:55:22 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*realloc(void *ptr, size_t size)
{
	void	*cursor;
	void	*new_ptr;

	new_ptr = NULL;
	if ((cursor = ft_try_tiny(ptr)))
		new_ptr = ft_make_realloc_tiny(ptr, size);
	else if ((cursor = ft_try_small(ptr)))
		new_ptr = ft_make_realloc_small(ptr, size);
	else if ((cursor = ft_try_large(ptr)))
		new_ptr = ft_make_realloc_large(ptr, size);
	else
		new_ptr = malloc(size);
	return (new_ptr);
}
