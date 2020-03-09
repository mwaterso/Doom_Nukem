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

void	parse_mtl_loop(t_line *list, t_lst_mtl *new)
{
	if (ft_strnequ_word(list->line, "Ka ", 3))
		sort_color(list->line, &(new->mtl.ka));
	if (ft_strnequ_word(list->line, "Kd ", 3) &&
	ft_isdigit((*list->line + 3)))
		sort_color(list->line, &(new->mtl.kd));
}

void	free_file_obj(t_file_obj file)
{
	if (file.lst)
		free_file(&(file.lst));
	if (file.v)
		ft_memdel((void **)&file.v);
	if (file.vt)
		ft_memdel((void **)&file.vt);
	if (file.vn)
		ft_memdel((void **)&file.vn);
}

void	free_file(t_lst_mtl **lst)
{
	t_lst_mtl	*head;
	t_lst_mtl	*next;

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
}

void	push_front_mtl(t_lst_mtl *new, t_lst_mtl **mtl)
{
	if (!mtl)
		*mtl = new;
	else
	{
		new->next = *mtl;
		*mtl = new;
	}
}

char	*sort_material(char *line)
{
	int			i;
	char		*str;

	i = 0;
	while (line[++i])
		if (line[i] == ' ')
			break ;
	if (!(str = ft_strdup(line + (i + 1))))
		return (NULL);
	return (str);
}
