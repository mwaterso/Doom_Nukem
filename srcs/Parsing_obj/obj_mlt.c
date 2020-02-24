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


void            free_fdot(t_fdot **dot)
{
    int i;
    int len;

    i = 0;
    len = sizeof(*dot) / sizeof(t_fdot);
    while (i < len)
        free(dot[i++]);
    dot = NULL;
}

void            free_2d(t_2d **dot)
{
    int i;
    int len;

    i = 0;
    len = sizeof(*dot) / sizeof(t_fdot);
    while (i < len)
        free(dot[i++]);
    dot = NULL;
}

void            free_file(t_file_obj *file)
{
    t_lst_mtl		*head;
	t_lst_mtl		*next;

    head = file->lst;
    while (head != NULL)
	{
		next = head->next;
		if (head->name)
			ft_strdel(&head->name);
		ft_memdel((void **)&head);
		head = next;
	}
	file->lst = NULL;
	head = NULL;
	next = NULL;
    free_fdot(&(file->v));
	free_2d(&(file->vt));
	free_fdot(&(file->vn));
}

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
