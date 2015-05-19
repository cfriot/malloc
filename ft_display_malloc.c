/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_malloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/01 04:49:16 by cfriot            #+#    #+#             */
/*   Updated: 2015/03/23 15:56:30 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>

int			ft_strlen_malloc(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

void		ft_putstr_malloc(char *str)
{
	int		nb;

	nb = ft_strlen_malloc(str);
	write(1, str, nb);
}

void		ft_putchar_malloc(char c)
{
	write(1, &c, 1);
}

void		ft_putbase_malloc(long nbr, int base)
{
	if (nbr < 0)
		nbr = -nbr;
	if (nbr > (base - 1))
	{
		ft_putbase_malloc(nbr / base, base);
		ft_putbase_malloc(nbr % base, base);
	}
	else
	{
		if (nbr < 10)
			ft_putchar_malloc(nbr + '0');
		else
			ft_putchar_malloc(nbr + 'a' - 10);
	}
}

void		show_alloc_mem(void)
{
	t_lrg	*cursor;
	long	tot;

	tot = 0;
	tot += show_tiny();
	tot += show_small();
	if ((cursor = g_env.lrg))
	{
		ft_putstr_malloc("LARGE : \n");
		while (cursor)
		{
			ft_putstr_malloc("0x");
			ft_putbase_malloc((long)cursor->addr, 16);
			ft_putstr_malloc("  -  0x");
			ft_putbase_malloc((long)cursor->addr + (long)cursor->size - 1, 16);
			ft_putstr_malloc("  :  ");
			ft_putbase_malloc(cursor->size, 10);
			tot += cursor->size;
			ft_putstr_malloc(" octets\n");
			cursor = cursor->next;
		}
	}
	else
		ft_putstr_malloc("LARGE : NULL\n");
	ft_print_tot(tot);
}
