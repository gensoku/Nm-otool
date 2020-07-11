/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_handle_64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 04:20:26 by tsedigi           #+#    #+#             */
/*   Updated: 2018/07/30 04:20:28 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int					get_section_64(struct segment_command_64 *seg)
{
	unsigned int			i;
	struct section_64		*sec;

	if (check_valid_file((void *)seg, sizeof(struct segment_command_64)))
		return (nm_display_err(NULL, NM_NO_SEG));
	if (check_valid_file((void *)seg, sizeof(struct segment_command_64)
		+ seg->nsects * sizeof(struct section_64)))
	{
		return (nm_display_err(NULL, NM_NO_SEC));
	}
	sec = (void *)seg + sizeof(*seg);
	i = 0;
	while (i < seg->nsects)
	{
		if (add_section_64(get_nm_env(NULL), sec))
			return (1);
		sec = (void *)sec + sizeof(*sec);
		i++;
	}
	return (0);
}

static int					get_symtab_64(struct symtab_command *sym,
	void *data)
{
	unsigned int			i;
	char					*stringtable;
	struct nlist_64			*table;

	i = 0;
	if (check_valid_file((void *)sym, sizeof(struct symtab_command)))
		return (nm_display_err(NULL, NM_NO_SYMCMD));
	if (check_valid_file(data, sym->stroff))
		return (nm_display_err(NULL, NM_NO_STRTAB));
	if (check_valid_file(data, sym->symoff + sym->nsyms * sizeof(*table)))
		return (nm_display_err(NULL, NM_NO_SYMTAB));
	stringtable = (void *)data + sym->stroff;
	table = (void *)data + sym->symoff;
	while (i < sym->nsyms)
	{
		if (add_table_64(table[i], stringtable))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int							nm_handle_64(void *data, unsigned int i)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	int						ret;

	header = (struct mach_header_64 *)data;
	if (check_valid_file(data, sizeof(*header)))
		return (nm_display_err(NULL, NM_NO_HD));
	if (check_valid_file(data, sizeof(*header) + header->ncmds
		* sizeof(struct load_command)))
		return (nm_display_err(NULL, NM_NO_LC));
	lc = (void *)data + sizeof(*header);
	ret = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			ret = get_symtab_64((struct symtab_command *)lc, data);
		else if (lc->cmd == LC_SEGMENT_64)
			ret = get_section_64((struct segment_command_64 *)lc);
		i++;
		lc = (void *)lc + lc->cmdsize;
		if (ret)
			return (EXIT_FAILURE);
	}
	nm_display_all(get_nm_env(NULL));
	return (EXIT_SUCCESS);
}
