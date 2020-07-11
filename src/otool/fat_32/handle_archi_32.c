/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_archi_32.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 06:45:10 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/05 06:45:11 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void				set_exe_archi(t_ot_env *env, char archi)
{
	char				*name;

	name = ft_strdup(archi
		== OT_POWER_PC ? OT_PPC_PRINT : OT_I386_PRINT);
	env->archi_name ? free(env->archi_name) : 0;
	env->archi_name = name;
}

static int				arch_contain_64(unsigned int n, struct fat_arch *arch)
{
	unsigned int		i;

	i = 0;
	while (i < n)
	{
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
			return (1);
		i++;
		arch = (void *)arch + sizeof(*arch);
	}
	return (0);
}

void					cpu_powerpc_32(unsigned int narch,
	void *data, struct fat_arch *arch)
{
	get_ot_env(NULL)->curr_archi = OT_POWER_PC;
	narch > 1 ? set_exe_archi(get_ot_env(NULL), OT_POWER_PC) : 0;
	get_ot_env(NULL)->addr = (void *)data + swap_uint32(arch->offset);
	archi_((void *)data + swap_uint32(arch->offset));
	ot_destroy_env(get_ot_env(NULL), OT_LET_NAME);
}

int						cpu_x86_64_32(unsigned int f, void *data,
	struct fat_arch *arch)
{
	f++;
	get_ot_env(NULL)->fat_enabled = 1;
	get_ot_env(NULL)->curr_archi = OT_X86_64;
	if (f == 1)
	{
		get_ot_env(NULL)->addr = (void *)data + swap_uint32(arch->offset);
		archi_((void *)data + swap_uint32(arch->offset));
		ot_destroy_env(get_ot_env(NULL), OT_LET_NAME);
	}
	return (f);
}

void					cpu_x86_32(unsigned int narch, struct fat_header *h,
	void *data, struct fat_arch *arch)
{
	if (narch == 1 || !arch_contain_64(narch, (void *)h + sizeof(*h)))
	{
		get_ot_env(NULL)->fat_enabled = 1;
		if (swap_uint32(arch->cputype) == CPU_TYPE_I386)
		{
			get_ot_env(NULL)->curr_archi = OT_I386;
			narch > 1 ? set_exe_archi(get_ot_env(NULL), OT_I386) : 0;
		}
		else
			get_ot_env(NULL)->curr_archi = OT_X86;
		get_ot_env(NULL)->addr = (void *)data + swap_uint32(arch->offset);
		archi_((void *)data + swap_uint32(arch->offset));
		ot_destroy_env(get_ot_env(NULL), OT_LET_NAME);
	}
}
