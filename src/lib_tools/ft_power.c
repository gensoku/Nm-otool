/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 02:56:03 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/10 02:56:04 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool_lib.h"

int		ft_power(int x, unsigned int y)
{
	if (y == 0)
		return (1);
	else if (y % 2 == 0)
		return (ft_power(x, y / 2) * ft_power(x, y / 2));
	else
		return (x * ft_power(x, y / 2) * ft_power(x, y / 2));
}
