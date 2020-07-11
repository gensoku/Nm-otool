/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 05:14:19 by tsedigi           #+#    #+#             */
/*   Updated: 2018/08/27 05:14:21 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool_lib.h"

int						size_ulong(unsigned long val)
{
	int					ret;

	if (!val)
		return (0);
	ret = 1;
	while (val > 10)
	{
		ret++;
		val /= 10;
	}
	return (ret);
}

unsigned int			size_uint(unsigned int x)
{
	unsigned int		ret;

	ret = 1;
	while (x > 9)
	{
		ret++;
		x /= 10;
	}
	return (ret);
}
