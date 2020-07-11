/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_handle_64_big.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 04:44:57 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/05 04:44:58 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int					get_section_64_big(struct segment_command_64 *seg,
	unsigned int i)
{
	struct section_64		*sec;
	unsigned int			nsects;

	if (check_valid_file((void *)seg, sizeof(struct segment_command_64)))
		return (ot_display_err(NULL, OT_NO_SEG));
	if (check_valid_file((void *)seg, sizeof(struct segment_command_64)
		+ swap_uint32(seg->nsects) * sizeof(struct section_64)))
		return (ot_display_err(NULL, OT_NO_SEC));
	sec = (void *)seg + sizeof(*seg);
	nsects = swap_uint32(seg->nsects);
	while (i < nsects)
	{
		if (is_opt_set(get_ot_env(NULL)->opts, 't')
			&& !ft_strcmp(sec->sectname, SECT_TEXT)
			&& !ft_strcmp(sec->segname, SEG_TEXT))
			return (add_section_64_big(get_ot_env(NULL), sec));
		else if (is_opt_set(get_ot_env(NULL)->opts, 'd')
			&& !ft_strcmp(sec->sectname, SECT_DATA)
			&& !ft_strcmp(sec->segname, SEG_DATA))
			return (add_section_64_big(get_ot_env(NULL), sec));
		sec = (void *)sec + sizeof(*sec);
		i++;
	}
	return (0);
}

static int					handle_loop_64_big(void *data,
	struct mach_header_64 *header, unsigned int i, t_ot_env *env)
{
	unsigned int			ncmds;
	struct load_command		*lc;

	lc = (void *)data + sizeof(*header);
	ncmds = swap_uint32(header->ncmds);
	while (i < ncmds)
	{
		if (swap_uint32(lc->cmd) == LC_SEGMENT_64)
			get_section_64_big((struct segment_command_64 *)lc, 0);
		if (env->sections)
		{
			ot_display_all(env);
			return (EXIT_SUCCESS);
		}
		i++;
		lc = (void *)lc + swap_uint32(lc->cmdsize);
	}
	return (EXIT_FAILURE);
}

int							ot_handle_64_big(void *data)
{
	struct mach_header_64	*header;
	t_ot_env				*env;

	header = (struct mach_header_64 *)data;
	env = get_ot_env(NULL);
	env->archi = 64;
	env->endian = BIG_END;
	if (is_opt_set(env->opts, 't') || is_opt_set(env->opts, 'd'))
		dis_name(env);
	if (check_valid_file(data, sizeof(*header)))
		return (ot_display_err(NULL, OT_NO_HD));
	if (check_valid_file(data, sizeof(*header) + swap_uint32(header->ncmds)
		* sizeof(struct load_command)))
		return (ot_display_err(NULL, OT_NO_LC));
	if (is_opt_set(env->opts, 'h'))
	{
		env->hd = header;
		ot_display_all(env);
		return (EXIT_SUCCESS);
	}
	if (is_opt_set(env->opts, 't') || is_opt_set(env->opts, 'd'))
		return (handle_loop_64_big(data, header, 0, env));
	return (EXIT_FAILURE);
}
