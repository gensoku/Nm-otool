/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conver_base_unsigned.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 05:23:38 by tsedigi           #+#    #+#             */
/*   Updated: 2018/08/27 05:23:39 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool_lib.h"
#include <stdlib.h>

char			*ft_strjoin_c_front(char *str, char c)
{
	int			size;
	int			i;
	char		*new;

	size = ft_strlen(str);
	i = 0;
	if ((new = (char *)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	new[0] = c;
	if (str)
	{
		while (str[i])
		{
			new[i + 1] = str[i];
			i++;
		}
	}
	new[i + 1] = '\0';
	return (new);
}

static char		conv_h(char maj, int n)
{
	char c;

	c = 0;
	if (n >= 0 && n <= 9)
		c = n + 48;
	else if (n == 10)
		c = (maj) ? 'A' : 'a';
	else if (n == 11)
		c = (maj) ? 'B' : 'b';
	else if (n == 12)
		c = (maj) ? 'C' : 'c';
	else if (n == 13)
		c = (maj) ? 'D' : 'd';
	else if (n == 14)
		c = (maj) ? 'E' : 'e';
	else if (n == 15)
		c = (maj) ? 'F' : 'f';
	return (c);
}

char			*conver_base_unsigned(char maj, unsigned long x, int base)
{
	char		*ret;
	char		*tmp;

	ret = NULL;
	while (x)
	{
		tmp = ft_strdup(ret);
		if (ret)
			free(ret);
		ret = ft_strjoin_c_front(tmp, conv_h(maj, x % base));
		if (tmp)
			free(tmp);
		x = x / base;
	}
	return (ret);
}
