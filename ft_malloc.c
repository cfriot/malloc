/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 07:16:48 by cfriot            #+#    #+#             */
/*   Updated: 2015/03/23 17:23:46 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_env	g_env;

void	free(void *addr)
{
	void	*cursor;

	if (addr != NULL)
	{
		if ((cursor = ft_try_tiny(addr)))
			ft_free_tiny(addr, (t_tin *)cursor);
		else if ((cursor = ft_try_small(addr)))
			ft_free_small(addr, (t_sml *)cursor);
		else
			ft_free_large(addr);
	}
}

void	*malloc(size_t size)
{
	void			*ptr;
	static int		first;

	if (!first)
	{
		ft_ini_env();
		first = 1;
	}
	if (size <= 1024)
		ptr = ft_malloc_tiny(size);
	else if (size <= 4096)
		ptr = ft_malloc_small(size);
	else
		ptr = ft_malloc_large(size);
	return (ptr);
}

void	*ft_malloc_small(size_t size)
{
	void		*ptr;
	size_t		i;

	i = ((sizeof(t_sml) / 4096) + 1) * 4096;
	if (!g_env.sml)
	{
		g_env.sml = mmap(0, i,
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		ft_ini_sml(g_env.sml);
	}
	ptr = ft_run_sml_lst(size);
	return (ptr);
}

void	*ft_malloc_tiny(size_t size)
{
	void		*ptr;
	long		i;

	i = ((sizeof(t_tin) / 4096) + 1) * 4096;
	if (!g_env.tin)
	{
		g_env.tin = mmap(0, i,
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		ft_ini_tin(g_env.tin);
	}
	ptr = ft_run_tin_lst(size);
	return (ptr);
}

void	*ft_malloc_large(size_t size)
{
	t_lrg	*lrg;
	t_lrg	*cursor;

	if ((lrg = mmap(0, ((sizeof(t_lrg) / 4096) + 1) * 4096,
					PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
	{
		cursor = g_env.lrg;
		lrg->addr = mmap(0, ((size / 4096) + 1) * 4096,
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		lrg->size = size;
		lrg->next = NULL;
	}
	if (g_env.lrg == NULL)
		g_env.lrg = lrg;
	else
	{
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = lrg;
	}
	return (lrg->addr);
}
