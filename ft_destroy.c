/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 16:27:52 by cfriot            #+#    #+#             */
/*   Updated: 2015/03/23 15:59:45 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_destroy_sml(t_sml *sml)
{
	t_sml	*cursor;
	long	i;

	cursor = g_env.sml;
	if (cursor == sml)
		g_env.sml = cursor->next;
	else
	{
		while (cursor->next != sml)
			cursor = cursor->next;
		cursor->next = sml->next;
	}
	i = ((sizeof(t_sml) / 4096) + 1) * 4096;
	munmap(sml, (size_t)i);
}

void	ft_destroy_tin(t_tin *tin)
{
	t_tin	*cursor;
	long	i;

	cursor = g_env.tin;
	if (cursor == tin)
		g_env.tin = cursor->next;
	else
	{
		while (cursor->next != tin)
			cursor = cursor->next;
		cursor->next = tin->next;
	}
	i = ((sizeof(t_tin) / 4096) + 1) * 4096;
	munmap(tin, (size_t)i);
}

void	ft_clear_tiny(t_tin *tin)
{
	int		i;
	int		j;

	i = -1;
	if (tin == NULL)
		return ;
	while (++i < 1600)
	{
		if (tin->tiny[i][2] == 0)
		{
			j = i;
			while (j < 1600 && tin->tiny[j][2] == 0)
				j++;
			j = j - i;
			tin->tiny[i][1] = j * 64;
			i = i + j;
		}
	}
}

void	ft_clear_small(t_sml *sml)
{
	int		i;
	int		j;

	i = -1;
	if (sml == NULL)
		return ;
	while (++i < 1600)
	{
		if (sml->small[i][2] == 0)
		{
			j = i;
			while (j < 1600 && sml->small[j][2] == 0)
				j++;
			j = j - i;
			sml->small[i][1] = j * 256;
			i = i + j;
		}
	}
}
