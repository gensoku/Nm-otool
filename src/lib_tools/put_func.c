/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 05:50:32 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/07 05:50:33 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool_lib.h"

int			ft_nlen_char(char *str, int n, char delim)
{
	int		x;

	x = 0;
	if (!str || !n || !delim)
		return (0);
	while (x < n && str[x] && str[x] != delim)
		x++;
	return (n - x);
}

void		ft_loop_char(unsigned int x, char c)
{
	while (x)
	{
		ft_putchar(c);
		x--;
	}
}

int			put_nstr_delim(char *str, int n, char delim)
{
	int		i;

	if (!str || !n)
		return (0);
	i = 0;
	while (i < n && str[i] && str[i] != delim)
	{
		ft_putchar(str[i]);
		i++;
	}
	return (n - i);
}
