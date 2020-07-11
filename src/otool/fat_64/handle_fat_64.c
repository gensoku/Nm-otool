/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat_64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 06:45:40 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/05 06:45:41 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void				mask_cpu_64(unsigned int to_mask)
{
	char				*conv;

	conv = conver_base_unsigned(0, to_mask, 16);
	if (ft_strlen(conv) > 1)
	{
		ft_putchar(conv[0]);
		ft_putchar(conv[1]);
	}
	else if (ft_strlen(conv) > 0)
		ft_putchar(conv[0]);
	ft_putendl("");
	conv ? ft_memdel((void **)&conv) : 0;
}

static void				print_fat_arch(struct fat_arch_64 *arch)
{
	unsigned int		to_mask;

	ft_putstr("\n    cputype ");
	ft_putnbr(swap_uint32(arch->cputype));
	ft_putstr("\n    cpusubtype ");
	to_mask = swap_uint32(arch->cpusubtype) & SUB_TYPE_MASK;
	ft_putnbr(to_mask);
	ft_putstr("\n    capabilities 0x");
	to_mask = swap_uint32(arch->cpusubtype) & CPU_SUBTYPE_MASK;
	if (to_mask)
		mask_cpu_64(to_mask);
	else
		ft_putendl("0");
	ft_putstr("    offset ");
	ft_putnbr(swap_uint64(arch->offset));
	ft_putstr("\n    size ");
	ft_putnbr(swap_uint64(arch->size));
	ft_putstr("\n    align 2^");
	ft_putnbr(swap_uint32(arch->align));
	ft_putstr(" (");
	ft_putnbr(ft_power(2, swap_uint32(arch->align)));
	ft_putendl(")");
}

static int				fat_print_header(struct fat_arch_64 *arch,
	unsigned int narch)
{
	unsigned int		i;
	char				*conv;

	i = 0;
	ft_putendl("Fat headers");
	ft_putstr("fat_magic 0x");
	conv = conver_base_unsigned(0, swap_uint32(get_ot_env(NULL)->magic), 16);
	ft_putendl(conv);
	conv ? ft_memdel((void **)&conv) : 0;
	ft_putstr("nfat_arch ");
	ft_putnbr(narch);
	ft_putchar('\n');
	while (i < narch)
	{
		ft_putstr("architecture ");
		ft_putnbr(i);
		print_fat_arch(arch);
		arch = (void *)arch + sizeof(*arch);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int				fat_loop_arch(void *data, struct fat_arch_64 *arch,
	unsigned int narch, unsigned int f)
{
	struct fat_header	*h;
	unsigned int		i;

	f = 0;
	h = (struct fat_header *)data;
	i = 0;
	while (i < narch)
	{
		if (check_valid_file((void *)data, swap_uint64(arch->offset)))
			return (ot_display_err(NULL, OT_NO_AROFF));
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

int						handle_fat_64(void *data, unsigned int f)
{
	struct fat_header	*h;
	struct fat_arch_64	*arch;
	unsigned int		narch;
	t_ot_env			*env;

	h = (struct fat_header *)data;
	env = get_ot_env(NULL);
	if (check_valid_file((void *)data, sizeof(struct fat_header)))
		return (ot_display_err(NULL, OT_NO_FATHD));
	arch = (void *)h + sizeof(*h);
	narch = swap_uint32(h->nfat_arch);
	if (check_valid_file(data, sizeof(*h) + narch * sizeof(*arch)))
		return (ot_display_err(NULL, OT_NO_FATAR));
	if (is_opt_set(env->opts, 'h') || is_opt_set(env->opts, 't')
		|| is_opt_set(env->opts, 'd'))
		return (fat_loop_arch(data, arch, narch, f));
	else if (is_opt_set(env->opts, 'f'))
		return (fat_print_header(arch, narch));
	return (EXIT_SUCCESS);
}
