/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 09:43:56 by cfriot            #+#    #+#             */
/*   Updated: 2015/03/23 15:56:48 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_ini_env(void)
{
	g_env.lrg = NULL;
	g_env.sml = NULL;
	g_env.tin = NULL;
}

void	ft_ini_sml(t_sml *sml)
{
	int		i;

	i = -1;
	sml->addr = mmap(0, 4096 * 100,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	sml->nb_small = 0;
	sml->tot_size_small = 0;
	sml->tot_block = 0;
	sml->next = NULL;
	while (++i < 1600)
	{
		sml->small[i][0] = 0;
		sml->small[i][1] = -1;
		sml->small[i][2] = 0;
	}
	ft_clear_small(sml);
}

void	ft_ini_tin(t_tin *tin)
{
	int		i;

	i = -1;
	tin->addr = mmap(0, 1024 * 100,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	tin->nb_tiny = 0;
	tin->tot_size_tiny = 0;
	tin->tot_block = 0;
	tin->next = NULL;
	while (++i < 1600)
	{
		tin->tiny[i][0] = 0;
		tin->tiny[i][1] = -1;
		tin->tiny[i][2] = 0;
	}
	ft_clear_tiny(tin);
}
