/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 16:07:02 by cfriot            #+#    #+#             */
/*   Updated: 2015/03/23 16:06:20 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*ft_make_realloc_small(void *ptr, size_t size)
{
	t_sml	*cursor;
	void	*new_ptr;
	int		i;

	new_ptr = NULL;
	cursor = ft_try_small(ptr);
	i = ((long)cursor->addr - (long)ptr);
	if (i % 256 == 0)
	{
		i = i / 256;
		new_ptr = malloc(size);
		new_ptr = ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}

void	*ft_make_realloc_tiny(void *ptr, size_t size)
{
	t_tin	*cursor;
	void	*new_ptr;
	int		i;

	new_ptr = NULL;
	cursor = ft_try_tiny(ptr);
	i = ((long)cursor->addr - (long)ptr);
	if (i % 64 == 0)
	{
		i = i / 64;
		new_ptr = malloc(size);
		new_ptr = ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}

void	*ft_make_realloc_large(void *ptr, size_t size)
{
	t_lrg	*cursor;
	void	*new_ptr;

	new_ptr = NULL;
	cursor = ft_try_large(ptr);
	new_ptr = malloc(size);
	new_ptr = ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}
