/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_archi_64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 02:07:18 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/04 02:07:19 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void				set_exe_archi(t_nm_env *env, char archi)
{
	char				*name;

	name = ft_strdup(archi
		== NM_POWER_PC ? NM_PPC_PRINT : NM_I386_PRINT);
	env->archi_name ? free(env->archi_name) : 0;
	env->archi_name = name;
}

static int				arch_contain_64(unsigned int n,
	struct fat_arch_64 *arch)
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

void					cpu_powerpc_64(unsigned int narch,
	void *data, struct fat_arch_64 *arch)
{
	get_nm_env(NULL)->curr_archi = NM_POWER_PC;
	narch > 1 ? set_exe_archi(get_nm_env(NULL), NM_POWER_PC) : 0;
	archi_((void *)data + swap_uint64(arch->offset));
	nm_destroy_env(get_nm_env(NULL), NM_LET_NAME);
}

int						cpu_x86_64_64(unsigned int f, void *data,
	struct fat_arch_64 *arch)
{
	f++;
	get_nm_env(NULL)->fat_enabled = 1;
	get_nm_env(NULL)->curr_archi = NM_X86_64;
	if (f == 1)
	{
		archi_((void *)data + swap_uint64(arch->offset));
		nm_destroy_env(get_nm_env(NULL), NM_LET_NAME);
	}
	return (f);
}

void					cpu_x86_64(unsigned int narch, struct fat_header *h,
	void *data, struct fat_arch_64 *arch)
{
	if (narch == 1 || !arch_contain_64(narch, (void *)h + sizeof(*h)))
	{
		get_nm_env(NULL)->fat_enabled = 1;
		if (swap_uint32(arch->cputype) == CPU_TYPE_I386)
		{
			get_nm_env(NULL)->curr_archi = NM_I386;
			narch > 1 ? set_exe_archi(get_nm_env(NULL), NM_I386) : 0;
		}
		else
			get_nm_env(NULL)->curr_archi = NM_X86;
		archi_((void *)data + swap_uint64(arch->offset));
		nm_destroy_env(get_nm_env(NULL), NM_LET_NAME);
	}
}
