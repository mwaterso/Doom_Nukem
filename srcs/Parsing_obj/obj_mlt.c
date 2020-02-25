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


void            free_fdot(t_fdot **dot, int size)
{
    int i;

    i = 0;
    dprintf(1, "SIZE1 =%d\n", size);
    while (i <= size)
    {
        dprintf(1, "\t\tdot = x:%f | y:%f | z:%f\n", dot[i]->x, dot[i]->y, dot[i]->z);
        free(dot[i++]);
    }
    dprintf(1, "OUT\n");
    dot = NULL;
}

void            free_2d(t_2d **dot, int size)
{
    int i;

    i = 0;
    dprintf(1, "SIZE =%d\n", size);
    while (i < size)
        free(dot[i++]);
    dot = NULL;
}

void            free_file(t_lst_mtl **lst)
{
	t_lst_mtl		*head;
	t_lst_mtl		*next;

	head = *lst;
	while (head != NULL)
	{
		next = head->next;
		if (head->name)
			ft_strdel(&head->name);
		ft_memdel((void **)&head);
		head = next;
	}
	*lst = NULL;
	head = NULL;
	next = NULL;
    // ft_memdel((void **)&file->v);
    // ft_memdel((void **)&file->vt);
    // ft_memdel((void **)&file->vn);
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
