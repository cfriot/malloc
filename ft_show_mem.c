/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/17 13:40:09 by cfriot            #+#    #+#             */
/*   Updated: 2015/03/23 15:22:47 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_display_info_tiny(t_tin *cursor)
{
	int		i;
	int		cpt;

	i = 0;
	cpt = 0;
	while (cursor->nb_tiny - cpt > 0)
	{
		if (cursor->tiny[i][0] != 0)
		{
			ft_putstr_malloc("0x");
			ft_putbase_malloc(cursor->tiny[i][0], 16);
			ft_putstr_malloc("  -  0x");
			ft_putbase_malloc(cursor->tiny[i][1] + cursor->tiny[i][0] - 1, 16);
			ft_putstr_malloc("  :  ");
			ft_putbase_malloc(cursor->tiny[i][1], 10);
			ft_putstr_malloc(" octets\n");
			cpt++;
		}
		i++;
	}
}

long	show_tiny(void)
{
	t_tin	*cursor;
	long	tot;

	tot = 0;
	if (g_env.tin == NULL)
		ft_putstr_malloc("TINY : NULL\n");
	else if ((cursor = g_env.tin))
	{
		while (cursor)
		{
			tot += cursor->tot_size_tiny;
			ft_putstr_malloc("TINY : 0x");
			ft_putbase_malloc((long)cursor->addr, 16);
			ft_putstr_malloc("\n");
			ft_display_info_tiny(cursor);
			cursor = cursor->next;
		}
	}
	return (tot);
}

void	ft_display_info_small(t_sml *cursor)
{
	int		i;
	int		cpt;

	i = 0;
	cpt = 0;
	while (cursor->nb_small - cpt > 0)
	{
		if (cursor->small[i][0] != 0)
		{
			ft_putstr_malloc("0x");
			ft_putbase_malloc(cursor->small[i][0], 16);
			ft_putstr_malloc("  -  0x");
			ft_putbase_malloc(cursor->small[i][1] +
					cursor->small[i][0] - 1, 16);
			ft_putstr_malloc("  :  ");
			ft_putbase_malloc(cursor->small[i][1], 10);
			ft_putstr_malloc(" octets\n");
			cpt++;
		}
		i++;
	}
}

long	show_small(void)
{
	t_sml	*cursor;
	long	tot;

	tot = 0;
	if (g_env.sml == NULL)
		ft_putstr_malloc("SMALL : NULL\n");
	else if ((cursor = g_env.sml))
	{
		while (cursor)
		{
			tot += cursor->tot_size_small;
			ft_putstr_malloc("SMALL : 0x");
			ft_putbase_malloc((long)cursor->addr, 16);
			ft_putstr_malloc("\n");
			ft_display_info_small(cursor);
			cursor = cursor->next;
		}
	}
	return (tot);
}

void	ft_print_tot(long tot)
{
	ft_putstr_malloc("TOTAL : ");
	ft_putbase_malloc(tot, 10);
	ft_putstr_malloc(" octets\n");
}
