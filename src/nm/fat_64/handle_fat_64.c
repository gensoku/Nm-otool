/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat_64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 01:11:01 by tsedigi           #+#    #+#             */
/*   Updated: 2018/08/10 01:11:02 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int						handle_fat_64(void *data,
	unsigned int i, unsigned int f)
{
	struct fat_header	*h;
	struct fat_arch_64	*arch;
	unsigned int		narch;

	h = (struct fat_header *)data;
	if (check_valid_file((void *)data, sizeof(struct fat_header)))
		return (nm_display_err(NULL, NM_NO_FATHD));
	arch = (void *)h + sizeof(*h);
	narch = swap_uint32(h->nfat_arch);
	if (check_valid_file(data, sizeof(*h) + narch * sizeof(*arch)))
		return (nm_display_err(NULL, NM_NO_FATAR));
	while (i < narch)
	{
		if (check_valid_file((void *)data, swap_uint64(arch->offset)))
			return (nm_display_err(NULL, NM_NO_AROFF));
		if (swap_uint32(arch->cputype) == CPU_TYPE_POWERPC)
			cpu_powerpc_64(narch, data, arch);
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
			f = cpu_x86_64_64(f, data, arch);
		else if (swap_uint32(arch->cputype) == CPU_TYPE_X86)
			cpu_x86_64(narch, h, data, arch);
		arch = (void *)arch + sizeof(*arch);
		i++;
	}
	return (EXIT_SUCCESS);
}
