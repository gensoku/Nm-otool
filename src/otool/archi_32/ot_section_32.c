/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_section_32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 04:41:46 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/05 04:41:48 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

#include <stdio.h>

int				add_section_32(t_ot_env *env, struct section *sec)
{
	t_section	*section;
	t_section	*tmp;

	if ((section = (t_section *)malloc(sizeof(t_section))) == NULL)
		return (ot_display_err(NULL, OT_MALLOC_FAIL));
	section->name = ft_strdup(sec->sectname);
	section->next = NULL;
	section->offset = sec->offset;
	section->addr = sec->addr;
	section->size = sec->size;
	tmp = env->sections;
	if (!tmp)
	{
		env->sections = section;
		section->id = 1;
		return (EXIT_SUCCESS);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = section;
	section->id = tmp->id + 1;
	return (EXIT_SUCCESS);
}
