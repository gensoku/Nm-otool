/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_section_64_big.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 04:45:02 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/05 04:45:03 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int				add_section_64_big(t_ot_env *env, struct section_64 *sec)
{
	t_section	*section;
	t_section	*tmp;

	if ((section = (t_section *)malloc(sizeof(t_section))) == NULL)
		return (ot_display_err(NULL, OT_MALLOC_FAIL));
	section->name = ft_strdup(sec->sectname);
	section->offset = swap_uint32(sec->offset);
	section->addr = swap_uint64(sec->addr);
	section->size = swap_uint64(sec->size);
	section->next = NULL;
	tmp = env->sections;
	if (!tmp)
	{
		env->sections = section;
		section->id = 1;
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = section;
	section->id = tmp->id + 1;
	return (0);
}
