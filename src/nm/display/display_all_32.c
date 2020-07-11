/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_all_32.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 04:23:12 by tsedigi           #+#    #+#             */
/*   Updated: 2018/08/27 04:23:13 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		dis_show_val(unsigned long value, int size)
{
	int			i;
	char		*hex;

	i = 0;
	hex = conver_base_unsigned(0, value, 16);
	i = size - ft_strlen(hex);
	while (i--)
		ft_putchar('0');
	ft_putstr(hex);
	hex ? ft_memdel((void **)&hex) : 0;
	ft_putchar(' ');
}

static void		dis_name_a_o(t_nm_env *env)
{
	if (env->archi_name)
	{
		ft_putchar('(');
		ft_putstr(env->archi_name);
		ft_putchar(')');
		ft_putstr(":");
	}
	ft_putstr(env->exe_name);
	ft_putstr(": ");
}

static void		dis_show_i386(t_table *tmp)
{
	if (tmp->show)
		dis_show_val(tmp->value, 8);
	else if (tmp->type != 'u' && tmp->type != 'U')
		ft_putstr("00000000 ");
	else
		ft_putstr("         ");
}

void			nm_display_32(t_table *tmp, t_nm_env *env)
{
	if (!tmp->debug)
	{
		if (is_opt_set(env->opts, 'A') || is_opt_set(env->opts, 'o'))
			dis_name_a_o(env);
		if (!is_opt_set(env->opts, 'u') && !is_opt_set(env->opts, 'j'))
		{
			if (env->curr_archi == NM_I386)
				dis_show_i386(tmp);
			else if (tmp->show)
				env->fat_enabled ? dis_show_val(tmp->value, 16)
					: dis_show_val(tmp->value, 8);
			else if (tmp->type != 'u' && tmp->type != 'U')
				env->fat_enabled ? ft_putstr("0000000000000000 ")
				: ft_putstr("00000000 ");
			else
				env->fat_enabled ? ft_putstr("                 ")
				: ft_putstr("         ");
			ft_putchar(tmp->type);
			ft_putchar(' ');
		}
		ft_putendl(tmp->name);
	}
}
