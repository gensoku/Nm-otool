/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_handle_32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 04:41:39 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/05 04:41:40 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int					get_section_32(struct segment_command *seg)
{
	unsigned int			i;
	struct section			*sec;

	if (check_valid_file((void *)seg, sizeof(struct segment_command)))
		return (ot_display_err(NULL, OT_NO_SEG));
	if (check_valid_file((void *)seg, sizeof(struct segment_command)
		+ seg->nsects * sizeof(struct section)))
		return (ot_display_err(NULL, OT_NO_SEC));
	sec = (void *)seg + sizeof(*seg);
	i = 0;
	while (i < seg->nsects)
	{
		if (is_opt_set(get_ot_env(NULL)->opts, 't')
			&& !ft_strcmp(sec->sectname, SECT_TEXT)
			&& !ft_strcmp(sec->segname, SEG_TEXT))
			return (add_section_32(get_ot_env(NULL), sec));
		else if (is_opt_set(get_ot_env(NULL)->opts, 'd')
			&& !ft_strcmp(sec->sectname, SECT_DATA)
			&& !ft_strcmp(sec->segname, SEG_DATA))
			return (add_section_32(get_ot_env(NULL), sec));
		sec = (void *)sec + sizeof(*sec);
		i++;
	}
	return (0);
}

static int					handle_loop_32(void *data,
	struct mach_header *header, unsigned int i, t_ot_env *env)
{
	struct load_command		*lc;

	lc = (void *)data + sizeof(*header);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
			get_section_32((struct segment_command *)lc);
		if (env->sections)
		{
			ot_display_all(env);
			return (EXIT_SUCCESS);
		}
		i++;
		lc = (void *)lc + lc->cmdsize;
	}
	return (EXIT_FAILURE);
}

int							ot_handle_32(void *data)
{
	struct mach_header		*header;
	t_ot_env				*env;

	header = (struct mach_header *)data;
	env = get_ot_env(NULL);
	env->archi = 32;
	env->endian = LITTLE_END;
	if (is_opt_set(env->opts, 't') || is_opt_set(env->opts, 'd'))
		dis_name(env);
	if (check_valid_file(data, sizeof(*header)))
		return (ot_display_err(NULL, OT_NO_HD));
	if (check_valid_file(data, sizeof(*header) + header->ncmds
		* sizeof(struct load_command)))
		return (ot_display_err(NULL, OT_NO_LC));
	if (is_opt_set(env->opts, 'h'))
	{
		env->hd = (struct mach_header_64 *)data;
		ot_display_all(env);
		return (EXIT_SUCCESS);
	}
	if (is_opt_set(env->opts, 't') || is_opt_set(env->opts, 'd'))
		return (handle_loop_32(data, header, 0, env));
	return (EXIT_FAILURE);
}
