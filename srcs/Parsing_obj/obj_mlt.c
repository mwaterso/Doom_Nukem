/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_mlt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:39:23 by beduroul          #+#    #+#             */
/*   Updated: 2020/02/20 14:39:25 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			push_front_mtl(t_lst_mtl *new, t_lst_mtl **mtl)
{
	if (!mtl)
		*mtl = new;
	else
	{
		new->next = *mtl;
		*mtl = new;
	}
}

char    *sort_material(char *line)
{
    int i;
    char *str;

    i = 0;
    while (line[++i])
        if (line[i] == ' ')
            break ;
    if (!(str = ft_strdup(line + (i + 1))))
        return (NULL);
    return (str);
}
