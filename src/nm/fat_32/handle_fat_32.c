/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat_32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 05:56:19 by tsedigi           #+#    #+#             */
/*   Updated: 2018/08/09 05:56:20 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int						handle_fat_32(void *data,
	unsigned int i, unsigned int f, unsigned int narch)
{
	struct fat_header	*h;
	struct fat_arch		*arch;

	h = (struct fat_header *)data;
	if (check_valid_file((void *)data, sizeof(struct fat_header)))
		return (nm_display_err(NULL, NM_NO_FATHD));
	arch = (void *)h + sizeof(*h);
	narch = swap_uint32(h->nfat_arch);
	if (check_valid_file((void *)data,
		sizeof(*h) + narch * sizeof(struct fat_arch)))
		return (nm_display_err(NULL, NM_NO_FATAR));
	while (i < narch)
	{
		if (check_valid_file((void *)data, swap_uint32(arch->offset)))
			return (nm_display_err(NULL, NM_NO_AROFF));
		if (swap_uint32(arch->cputype) == CPU_TYPE_POWERPC)
			cpu_powerpc_32(narch, data, arch);
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
			f = cpu_x86_64_32(f, data, arch);
		else if (swap_uint32(arch->cputype) == CPU_TYPE_X86)
			cpu_x86_32(narch, h, data, arch);
		arch = (void *)arch + sizeof(*arch);
		i++;
	}
	return (EXIT_SUCCESS);
}
