/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_display_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 04:55:08 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/05 04:55:08 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

#include <stdio.h>

void			ot_display_all(t_ot_env *env)
{
	t_section	*tmp;
	int			pad;

	tmp = env->sections;
	pad = 0;
	if (is_opt_set(env->opts, 'h'))
	{
		if (env->endian == LITTLE_END)
			ot_display_h_l(env);
		else
			ot_display_h_b(env);
		return ;
	}
	pad = env->archi == 32 ? 8 : 16;
	if ((is_opt_set(env->opts, 't') || is_opt_set(env->opts, 'd')))
	{
		ot_display_sec(tmp, env, pad);
		return ;
	}
}
