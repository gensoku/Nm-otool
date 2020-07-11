/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_tables_64_big.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 01:34:09 by tsedigi           #+#    #+#             */
/*   Updated: 2018/08/12 01:34:10 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char				get_section_type(t_nm_env *env, unsigned char s)
{
	t_section			*section;

	if (!env->sections)
	{
		ft_putendl("error");
	}
	section = env->sections;
	while (section)
	{
		if (s == section->id)
		{
			if (!ft_strcmp(section->name, SECT_DATA))
				return ('d');
			else if (!ft_strcmp(section->name, SECT_BSS))
				return ('b');
			else if (!ft_strcmp(section->name, SECT_TEXT))
				return ('t');
			else
				return ('s');
		}
		section = section->next;
	}
	return ('s');
}

static char				get_type_64_big(struct nlist_64 *table)
{
	unsigned char		c;

	c = table->n_type;
	if (c & N_STAB)
		return ('-');
	c = table->n_type & N_TYPE;
	if (c == N_UNDF && table->n_value != 0)
		c = 'c';
	else if ((c == N_UNDF && table->n_value == 0) || c == N_PBUD)
		c = 'u';
	else if (c == N_ABS)
		c = 'a';
	else if (c == N_SECT)
		c = get_section_type(get_nm_env(NULL), table->n_sect);
	else if (c == N_INDR)
		c = 'i';
	else
		c = '?';
	if ((table->n_type & N_EXT) && c != '?')
		c -= 32;
	return (c);
}

int						add_table_64_big(struct nlist_64 table,
	char *stringtable)
{
	t_table				*t;

	if ((t = (t_table *)malloc(sizeof(t_table))) == NULL)
		return (nm_display_err(NULL, NM_MALLOC_FAIL));
	t->name = ft_strdup(stringtable + swap_uint32(table.n_un.n_strx));
	if (table.n_value)
		t->show = 1;
	else
		t->show = 0;
	t->value = swap_uint64(table.n_value);
	t->archi = 32;
	t->type = get_type_64_big(&table);
	t->debug = table.n_type & N_STAB ? 1 : 0;
	t->next = NULL;
	sort_push_table(get_nm_env(NULL), t);
	return (0);
}
