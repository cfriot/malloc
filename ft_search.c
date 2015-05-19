/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 16:37:38 by cfriot            #+#    #+#             */
/*   Updated: 2015/03/23 16:07:47 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*ft_try_tiny(void *addr)
{
	t_tin	*cursor;

	cursor = g_env.tin;
	while (cursor)
	{
		if ((long)addr >= (long)cursor->addr &&
				(long)addr <= (long)cursor->addr + 1024 * 100)
			return (cursor);
		cursor = cursor->next;
	}
	return (NULL);
}

void	*ft_try_small(void *addr)
{
	t_sml	*cursor;

	cursor = g_env.sml;
	while (cursor)
	{
		if ((long)addr >= (long)cursor->addr &&
				(long)addr <= (long)cursor->addr + 4096 * 100)
			return (cursor);
		cursor = cursor->next;
	}
	return (NULL);
}

void	*ft_try_large(void *addr)
{
	t_lrg	*cursor;

	cursor = g_env.lrg;
	while (cursor)
	{
		if (addr == cursor->addr)
			return (cursor);
		cursor = cursor->next;
	}
	return (NULL);
}
