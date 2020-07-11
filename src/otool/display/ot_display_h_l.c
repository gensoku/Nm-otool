/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_display_h_l.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 05:51:55 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/07 05:51:56 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	print_head(t_ot_env *env, char *mg)
{
	ft_putendl("Mach header");
	ft_putstr("      magic cputype cpusubtype  caps");
	ft_putendl("    filetype ncmds sizeofcmds      flags");
	mg = conver_base_unsigned(0, env->magic, 16);
	ft_putstr(" 0x");
	ft_putstr(mg);
	mg ? ft_memdel((void **)&mg) : 0;
}

static void	ot_display_h_l_2(t_ot_env *env, char *mg, unsigned int tmp)
{
	tmp = env->hd->filetype;
	ft_loop_char(ft_strlen("filetype") + 4 - size_uint(tmp), ' ');
	ft_putnbr(tmp);
	tmp = env->hd->ncmds;
	ft_loop_char(ft_strlen("ncmds") + 1 - size_uint(tmp), ' ');
	ft_putnbr(tmp);
	tmp = env->hd->sizeofcmds;
	ft_loop_char(ft_strlen("sizeofcmds") + 1 - size_uint(tmp), ' ');
	ft_putnbr(tmp);
	ft_loop_char(ft_strlen("flags") + 3 - 8, ' ');
	ft_putstr(" 0x");
	mg = conver_base_unsigned(0, env->hd->flags, 16);
	ft_loop_char(8 - ft_strlen(mg), '0');
	ft_putstr(mg);
	ft_putstr("\n");
	mg ? ft_memdel((void **)&mg) : 0;
}

void		ot_display_h_l(t_ot_env *env)
{
	unsigned int	tmp;
	char			*conv;

	print_head(env, NULL);
	tmp = env->hd->cputype;
	ft_loop_char(ft_strlen("cputype") + 1 - size_uint(tmp), ' ');
	if (ft_strlen("cputype") + 1 - size_uint(tmp) <= 0)
		ft_putchar(' ');
	ft_putnbr(tmp);
	tmp = env->hd->cpusubtype & SUB_TYPE_MASK;
	ft_loop_char(ft_strlen("cpusubtype") + 1 - size_uint(tmp), ' ');
	ft_putnbr(tmp);
	tmp = env->hd->cpusubtype & CPU_SUBTYPE_MASK;
	ft_loop_char(ft_strlen("caps") - 2 - 2, ' ');
	ft_putstr("  0x");
	conv = conver_base_unsigned(0, tmp, 16);
	if (conv && ft_strlen(conv) > 1)
	{
		ft_putchar(conv[0]);
		ft_putchar(conv[1]);
	}
	else
		ft_putstr("00");
	ot_display_h_l_2(env, NULL, 0);
	conv ? ft_memdel((void **)&conv) : 0;
}
