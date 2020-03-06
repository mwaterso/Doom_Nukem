/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:50:43 by beduroul          #+#    #+#             */
/*   Updated: 2020/03/06 15:50:44 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	free_new_lst(t_lst_mtl *new)
{
	ft_strdel(&(new->name));
	free(new);
	new = NULL;
}

void	free_object(t_object **obj, t_object *new)
{
	t_object		*tmp;
	t_object		*next;

	tmp = *obj;
	while (tmp)
	{
		next = tmp->next;
		ft_strdel(&(tmp->file));
		ft_strdel(&(tmp->l_file));
		free_poly(&(tmp->poly));
		free(tmp);
		tmp = next;
	}
	*obj = NULL;
	ft_strdel(&(new->file));
	ft_strdel(&(new->l_file));
	free(new);
	new = NULL;
}

int	parse_fobj2(t_line *list, t_file_obj *file, t_input *d, t_poly **poly)
{
	char *tmp;

	if (ft_strnequ_word(list->line, "mtllib ", 7))
		if (!(sort_mtl(d, list->line, file)))
			return (0);
	if (ft_strnequ_word(list->line, "v ", 2))
		if (!(sort_tfdot(list->line, &(file->v[file->index.i++]))))
			return (0);
	if (ft_strnequ_word(list->line, "vt ", 3))
		if (!(sort_t2d(list->line, &(file->vt[file->index.j++]))))
			return (0);
	if (ft_strnequ_word(list->line, "usemtl ", 7))
		tmp = list->line + 7;
	if (ft_strnequ_word(list->line, "vn ", 3))
		if (!(sort_tfdot(list->line, &(file->vn[file->index.k++]))))
			return (0);
	if (ft_strnequ_word(list->line, "f ", 2))
		if (!(sort_poly(list->line + 2, poly, *file, tmp)))
			return (0);
	return (1);
}
