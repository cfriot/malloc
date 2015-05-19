/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/20 13:07:11 by exam              #+#    #+#             */
/*   Updated: 2015/02/13 04:26:38 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	if (src)
	{
		dest = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
		if (dest)
		{
			while (src[i])
			{
				dest[i] = src[i];
				i++;
			}
			dest[i] = '\0';
		}
		return (dest);
	}
	else
		return (NULL);
}
