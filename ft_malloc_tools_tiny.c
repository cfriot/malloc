/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 08:48:18 by cfriot            #+#    #+#             */
/*   Updated: 2015/03/23 16:05:50 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*ft_run_tin_lst(size_t size)
{
	t_tin	*cursor;
	void	*ret;

	ret = NULL;
	cursor = g_env.tin;
	while (cursor && !ret)
	{
		ret = ft_search_space_tiny(size, cursor);
		if (ret)
			ft_clear_tiny(cursor);
		cursor = cursor->next;
	}
	if (!ret)
	{
		cursor = g_env.tin;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = mmap(0, ((sizeof(t_tin) / 4096) + 1) * 4096,
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		cursor = cursor->next;
		ft_ini_tin(cursor);
		ret = ft_search_space_tiny(size, cursor);
	}
	return (ret);
}

void	*ft_search_space_tiny(size_t size, t_tin *tin)
{
	int		i;

	i = -1;
	if (tin->tot_block + (((size / 64) + 1)) <= 1600)
	{
		while (++i <= 1600)
		{
			if (tin->tiny[i][2] == 0)
			{
				if (tin->tiny[i][1] % 64 == 0 || tin->tiny[i][1] == -1)
				{
					if ((size <= (size_t)tin->tiny[i][1]) ||
							(tin->tiny[i][1] == -1 && (long)tin->addr +
							(i * 64) + (long)size
							< (long)tin->addr + (1024 * 100)))
						return (ft_update_env_tiny(i, size, tin));
				}
			}
		}
	}
	return (NULL);
}

void	*ft_update_env_tiny(int i, size_t size, t_tin *tin)
{
	int		nb_case;

	if (size % 64 == 0)
		nb_case = size / 64;
	else
		nb_case = (size / 64) + 1;
	tin->tot_size_tiny += size;
	tin->tot_block += nb_case;
	if (tin->tiny[i][1] != -1)
		ft_check_leaks_tiny(i, nb_case, tin);
	while (--nb_case >= 0)
	{
		tin->tiny[i + nb_case][2] = 1;
		tin->tiny[i + nb_case][1] = 0;
	}
	tin->tiny[i][1] = size;
	tin->tiny[i][0] = (long)tin->addr + (i * 64);
	tin->nb_tiny++;
	return ((void *)tin->tiny[i][0]);
}

void	ft_check_leaks_tiny(int i, int nb_case, t_tin *tin)
{
	int old_size;

	old_size = tin->tiny[i][1];
	if (old_size % 64 == 0)
	{
		if (old_size / 64 > nb_case)
			tin->tiny[i + nb_case][1] = (((old_size / 64) - nb_case) * 64);
	}
	else
	{
		if ((old_size / 64) + 1 > nb_case)
			tin->tiny[i + nb_case][1] =
				((((old_size / 64) - nb_case) + 1) * 64);
	}
}

int		ft_free_tiny(void *addr, t_tin *tin)
{
	long	i;
	int		ret;
	int		nb_case;

	ret = 1;
	i = ((long)addr - (long)tin->addr) / 64;
	tin->tiny[i][0] = 0;
	tin->tot_size_tiny -= tin->tiny[i][1];
	if (tin->tiny[i][1] % 64 == 0)
		nb_case = tin->tiny[i][1] / 64;
	else
		nb_case = tin->tiny[i][1] / 64 + 1;
	tin->tot_block -= nb_case;
	tin->tiny[i][1] = nb_case * 64;
	while (--nb_case >= 0)
		tin->tiny[i + nb_case][2] = 0;
	tin->nb_tiny--;
	if (tin->tot_size_tiny == 0)
	{
		ret = munmap((caddr_t)tin->addr, 1024 * 100);
		tin->addr = NULL;
		ft_destroy_tin(tin);
	}
	return (ret);
}
