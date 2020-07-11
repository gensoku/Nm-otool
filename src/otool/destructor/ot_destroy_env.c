/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_destroy_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 03:42:59 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/05 03:42:59 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void		destroy_sections(t_ot_env *env)
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

void			ot_destroy_env(t_ot_env *env, char opt)
{
	if (!env)
		return ;
	if (opt == OT_DESTROY)
	{
		env->exe_name ? ft_memdel((void **)&(env->exe_name)) : 0;
		env->addr = NULL;
		env->size = 0;
	}
	env->archi_name ? ft_memdel((void **)&(env->archi_name)) : 0;
	env->file_type ? ft_memdel((void **)&(env->file_type)) : 0;
	env->fat_enabled = 0;
	env->endian = 0;
	env->magic = 0;
	env->archi = 0;
	ft_bzero((void **)&env->hd, sizeof(struct mach_header));
	env->curr_archi = 0;
	destroy_sections(env);
}
