/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 05:48:10 by tsedigi           #+#    #+#             */
/*   Updated: 2018/08/27 05:48:11 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		dis_name(t_nm_env *env)
{
	if (env->fat_enabled && !env->arch_enabled &&
		(!env->tables || env->tables->archi == 64))
	{
		return ;
	}
	if (env->print_path && !is_opt_set(env->opts, 'A')
		&& !is_opt_set(env->opts, 'o'))
	{
		ft_putendl("");
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
}

static int		check_opts_dis(t_nm_env *env, t_table *tmp)
{
	if ((is_opt_set(env->opts, 'u') && (tmp->type == 'u' || tmp->type == 'U'))
			&& !is_opt_set(env->opts, 'U'))
	{
		return (1);
	}
	if ((is_opt_set(env->opts, 'U') && (tmp->type != 'u' && tmp->type != 'U'))
			&& !is_opt_set(env->opts, 'u'))
	{
		return (1);
	}
	if (!is_opt_set(env->opts, 'u') && !is_opt_set(env->opts, 'U'))
		return (1);
	return (0);
}

void			nm_display_all(t_nm_env *env)
{
	t_table		*tmp;

	tmp = env->tables;
	dis_name(env);
	while (tmp)
	{
		if (!tmp->debug && tmp->archi == 32)
		{
			if (check_opts_dis(env, tmp))
				nm_display_32(tmp, env);
		}
		else if (!tmp->debug && tmp->archi == 64)
		{
			if (check_opts_dis(env, tmp))
				nm_display_64(tmp);
		}
		tmp = tmp->next;
	}
}
