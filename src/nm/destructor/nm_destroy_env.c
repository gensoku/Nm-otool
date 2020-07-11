/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_destroy_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 02:08:53 by tsedigi           #+#    #+#             */
/*   Updated: 2018/08/10 02:08:54 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		destroy_sections(t_nm_env *env)
{
	t_section	*tmp;
	t_section	*tmp2;

	tmp = env->sections;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		tmp2->name ? free(tmp2->name) : 0;
		free(tmp2);
	}
	env->sections = NULL;
}

static void		destroy_tables(t_nm_env *env)
{
	t_table		*tmp;
	t_table		*tmp2;

	tmp = env->tables;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		tmp2->name ? free(tmp2->name) : 0;
		free(tmp2);
	}
	env->tables = NULL;
}

void			nm_destroy_env(t_nm_env *env, char opt)
{
	if (!env)
		return ;
	if (opt == NM_DESTROY)
	{
		env->exe_name ? ft_memdel((void **)&(env->exe_name)) : 0;
		env->addr = NULL;
		env->size = 0;
	}
	env->archi_name ? ft_memdel((void **)&(env->archi_name)) : 0;
	env->fat_enabled = 0;
	env->curr_archi = 0;
	destroy_sections(env);
	destroy_tables(env);
}
