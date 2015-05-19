/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 08:48:18 by cfriot            #+#    #+#             */
/*   Updated: 2015/03/23 16:05:03 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*ft_run_sml_lst(size_t size)
{
	t_sml	*cursor;
	void	*ret;

	ret = NULL;
	cursor = g_env.sml;
	while (cursor && !ret)
	{
		ret = ft_search_space_small(size, cursor);
		if (ret)
			ft_clear_small(cursor);
		cursor = cursor->next;
	}
	if (!ret)
	{
		cursor = g_env.sml;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = mmap(0, ((sizeof(t_sml) / 4096) + 1) * 4096,
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		cursor = cursor->next;
		ft_ini_sml(cursor);
		ret = ft_search_space_small(size, cursor);
	}
	return (ret);
}

void	*ft_search_space_small(size_t size, t_sml *sml)
{
	int		i;

	i = -1;
	if (sml->tot_block + ((size / 256) + 1) <= 1600)
	{
		while (++i <= 1600)
		{
			if (sml->small[i][2] == 0)
			{
				if (sml->small[i][1] % 256 == 0 || sml->small[i][1] == -1)
				{
					if (size <= (size_t)sml->small[i][1] ||
							(sml->small[i][1] == -1 && (long)sml->addr +
							(i * 256) + (long)size <
							(long)sml->addr + (4096 * 100)))
						return (ft_update_env_small(i, size, sml));
				}
			}
		}
	}
	return (NULL);
}

void	*ft_update_env_small(int i, size_t size, t_sml *sml)
{
	int		nb_case;

	if (size % 256 == 0)
		nb_case = size / 256;
	else
		nb_case = (size / 256) + 1;
	sml->tot_size_small += size;
	sml->tot_block += nb_case;
	if (sml->small[i][1] != -1)
		ft_check_leaks_small(i, nb_case, sml);
	while (--nb_case >= 0)
	{
		sml->small[i + nb_case][2] = 1;
		sml->small[i + nb_case][1] = 0;
	}
	sml->small[i][1] = size;
	sml->small[i][0] = (long)sml->addr + (i * 256);
	sml->nb_small++;
	return ((void *)sml->small[i][0]);
}

void	ft_check_leaks_small(int i, int nb_case, t_sml *sml)
{
	int old_size;

	old_size = sml->small[i][1];
	if (old_size % 256 == 0)
	{
		if (old_size / 256 > nb_case)
			sml->small[i + nb_case][1] = (((old_size / 256) - nb_case) * 256);
	}
	else
	{
		if ((old_size / 256) + 1 > nb_case)
			sml->small[i + nb_case][1] =
				((((old_size / 256) - nb_case) + 1) * 256);
	}
}

int		ft_free_small(void *addr, t_sml *sml)
{
	long	i;
	int		ret;
	int		nb_case;

	ret = 1;
	i = ((long)addr - (long)sml->addr) / 256;
	sml->small[i][0] = 0;
	sml->tot_size_small -= sml->small[i][1];
	if (sml->small[i][1] % 256 == 0)
		nb_case = sml->small[i][1] / 256;
	else
		nb_case = sml->small[i][1] / 256 + 1;
	sml->tot_block -= nb_case;
	sml->small[i][1] = nb_case * 256;
	while (--nb_case >= 0)
		sml->small[i + nb_case][2] = 0;
	sml->nb_small--;
	if (sml->tot_size_small == 0)
	{
		ret = munmap(sml->addr, 4096 * 100);
		sml->addr = NULL;
		ft_destroy_sml(sml);
	}
	return (ret);
}
