/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_display_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 05:50:33 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/05 05:50:33 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

#include <stdio.h>

static void			ot_dump_hex(unsigned char x)
{
	static char	arr[16] = "0123456789abcdef";
	char		tmp;

	tmp = 0;
	if (!x)
	{
		ft_putstr("00");
		return ;
	}
	if (x > 15)
	{
		tmp = arr[x % 16];
		x /= 16;
		ft_putchar(arr[(unsigned short)x]);
		ft_putchar(tmp);
	}
	else
	{
		ft_putchar('0');
		if (!x)
			ft_putchar('0');
		else
			ft_putchar(arr[(unsigned short)x]);
	}
}

static void			put_zero(int size)
{
	while (size > 0)
	{
		ft_putchar('0');
		size--;
	}
}

void				ot_display_hex(void *data, unsigned long size,
	unsigned long addr, int pad)
{
	char			*str_adr;
	unsigned long	i;
	int				j;
	unsigned char	x;

	i = 0;
	j = 0;
	str_adr = NULL;
	while (i < size)
	{
		if (i == 0 || i % 16 == 0)
		{
			i != 0 ? ft_putstr("\n") : 0;
			str_adr = conver_base_unsigned(0, addr + i, 16);
			put_zero(pad - ft_strlen(str_adr));
			ft_putstr(str_adr);
			ft_putstr("\t");
			free(str_adr);
		}
		x = *((unsigned char *)((void *)data + i));
		ot_dump_hex(x);
		ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}
