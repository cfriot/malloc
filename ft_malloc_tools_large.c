/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_tools_large.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 17:15:26 by cfriot            #+#    #+#             */
/*   Updated: 2015/03/23 16:02:28 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int		ft_free_large(void *addr)
{
	t_lrg	*cursor;
	t_lrg	*previous;
	int		ret;

	previous = NULL;
	cursor = g_env.lrg;
	while (cursor)
	{
		if (cursor->addr == addr)
		{
			ret = munmap(cursor->addr, ((cursor->size / 4096) + 1) * 4096);
			if (cursor == g_env.lrg)
				g_env.lrg = cursor->next;
			else
				previous->next = cursor->next;
			munmap(cursor, ((sizeof(t_lrg) / 4096) + 1) * 4096);
			return (ret);
		}
		previous = cursor;
		if (cursor)
			cursor = cursor->next;
	}
	return (0);
}
