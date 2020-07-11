/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_all_64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 04:23:17 by tsedigi           #+#    #+#             */
/*   Updated: 2018/08/27 04:23:19 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		dis_show_val(unsigned long value)
{
	int			i;
	char		*hex;

	i = 0;
	hex = conver_base_unsigned(0, value, 16);
	i = 16 - ft_strlen(hex);
	while (i--)
		ft_putchar('0');
	ft_putstr(hex);
	hex ? ft_memdel((void **)&hex) : 0;
	ft_putchar(' ');
}

static void		dis_name_a_o(t_nm_env *env)
{
	ft_putstr(env->exe_name);
	ft_putstr(":");
	if (env->archi_name)
	{
		ft_putstr(env->archi_name);
		ft_putstr(":");
	}
	ft_putstr(" ");
}

void			nm_display_64(t_table *tmp)
{
	if (!tmp->debug)
	{
		if (is_opt_set(get_nm_env(NULL)->opts, 'A')
			|| is_opt_set(get_nm_env(NULL)->opts, 'o'))
			dis_name_a_o(get_nm_env(NULL));
		if (!is_opt_set(get_nm_env(NULL)->opts, 'u')
			&& !is_opt_set(get_nm_env(NULL)->opts, 'j'))
		{
			if (tmp->show)
				dis_show_val(tmp->value);
			else if (tmp->type != 'u' && tmp->type != 'U')
				ft_putstr("0000000000000000 ");
			else
				ft_putstr("                 ");
			ft_putchar(tmp->type);
			ft_putchar(' ');
		}
		ft_putendl(tmp->name);
	}
	tmp = tmp->next;
}
