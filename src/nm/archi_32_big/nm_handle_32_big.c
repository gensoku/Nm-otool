/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_handle_32_big.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 06:03:24 by tsedigi           #+#    #+#             */
/*   Updated: 2018/08/10 06:03:25 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int					get_section_32_big(struct segment_command *seg)
{
	unsigned int			i;
	struct section			*sec;
	unsigned int			nsects;

	if (check_valid_file((void *)seg, sizeof(struct segment_command)))
		return (nm_display_err(NULL, NM_NO_SEG));
	if (check_valid_file((void *)seg, sizeof(struct segment_command)
		+ swap_uint32(seg->nsects) * sizeof(struct section)))
	{
		return (nm_display_err(NULL, NM_NO_SEC));
	}
	sec = (void *)seg + sizeof(*seg);
	i = 0;
	nsects = swap_uint32(seg->nsects);
	while (i < nsects)
	{
		if (add_section_32_big(get_nm_env(NULL), sec))
			return (1);
		sec = (void *)sec + sizeof(*sec);
		i++;
	}
	return (0);
}

static int					get_symtab_32_big(struct symtab_command *sym,
	void *data)
{
	unsigned int			i;
	char					*stringtable;
	struct nlist			*table;
	unsigned int			nsyms;

	i = 0;
	if (check_valid_file((void *)sym, sizeof(struct symtab_command)))
		return (nm_display_err(NULL, NM_NO_SYMCMD));
	if (check_valid_file(data, swap_uint32(sym->stroff)))
		return (nm_display_err(NULL, NM_NO_STRTAB));
	if (check_valid_file(data, swap_uint32(sym->symoff)
		+ swap_uint32(sym->nsyms) * sizeof(*table)))
	{
		return (nm_display_err(NULL, NM_NO_SYMTAB));
	}
	stringtable = (void *)data + swap_uint32(sym->stroff);
	table = (void *)data + swap_uint32(sym->symoff);
	nsyms = swap_uint32(sym->nsyms);
	while (i < nsyms)
	{
		if (add_table_32_big(table[i], stringtable))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int							nm_handle_32_big(void *data,
	unsigned int i, int ret)
{
	struct mach_header		*header;
	struct load_command		*lc;
	unsigned int			ncmds;

	header = (struct mach_header *)data;
	if (check_valid_file(data, sizeof(*header)))
		return (nm_display_err(NULL, NM_NO_HD));
	if (check_valid_file(data, sizeof(*header) + swap_uint32(header->ncmds)
		* sizeof(struct load_command)))
		return (nm_display_err(NULL, NM_NO_LC));
	lc = (void *)data + sizeof(*header);
	ncmds = swap_uint32(header->ncmds);
	while (i < ncmds)
	{
		if (swap_uint32(lc->cmd) == LC_SYMTAB)
			ret = get_symtab_32_big((struct symtab_command *)lc, data);
		else if (swap_uint32(lc->cmd) == LC_SEGMENT)
			ret = get_section_32_big((struct segment_command *)lc);
		i++;
		lc = (void *)lc + swap_uint32(lc->cmdsize);
		if (ret)
			return (EXIT_FAILURE);
	}
	nm_display_all(get_nm_env(NULL));
	return (EXIT_SUCCESS);
}
