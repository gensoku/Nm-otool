/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_display_sec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 05:53:22 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/07 05:53:23 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void		dis_name(t_ot_env *env)
{
	if (env->file_type)
		ft_memdel((void **)&(env->file_type));
	ft_putstr(env->exe_name);
	if (env->archi_name)
	{
		ft_putstr("(");
		ft_putstr(env->archi_name);
		ft_putendl("):");
	}
	else
		ft_putendl(":");
}

void		ot_display_sec(t_section *tmp, t_ot_env *env, int pad)
{
	if (check_valid_file(env->addr, tmp->offset + tmp->size))
		return ;
	is_opt_set(env->opts, 't') ? ft_putstr(OT_SEC_TEXT)
		: ft_putstr(OT_SEC_DATA);
	if (env->curr_archi == OT_POWER_PC)
	{
		ot_display_hex_ppc((void *)env->addr + tmp->offset,
			tmp->size, tmp->addr, pad);
	}
	else
	{
		ot_display_hex((void *)env->addr + tmp->offset,
			tmp->size, tmp->addr, pad);
	}
}
