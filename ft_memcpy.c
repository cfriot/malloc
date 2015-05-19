/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:48:28 by cfriot            #+#    #+#             */
/*   Updated: 2015/03/20 18:19:50 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *dsttmp;
	char *srctmp;

	dsttmp = dst;
	srctmp = (char *)src;
	while (n > 0)
	{
		dsttmp[n - 1] = srctmp[n - 1];
		n--;
	}
	dst = dsttmp;
	return (dst);
}
