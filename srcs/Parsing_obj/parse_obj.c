/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_obj.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/13 21:13:57 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 21:14:06 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void			ft_sort_pos(char *line, t_object *new)
{
	if (ft_strrchr(line, 'x'))
		new->pos.x = ft_atof(ft_strrchr(line, 'x') + 2);
	if (ft_strrchr(line, 'y'))
		new->pos.y = ft_atof(ft_strrchr(line, 'y') + 2);
	if (ft_strrchr(line, 'z'))
		new->pos.z = ft_atof(ft_strrchr(line, 'z') + 2);
}

void			ft_sort_rot(char  *line, t_object *new)
{
	if (ft_strrchr(line, 'x'))
		new->rot.x = ft_atof(ft_strrchr(line, 'x') + 2);
	if (ft_strrchr(line, 'y'))
		new->rot.y = ft_atof(ft_strrchr(line, 'y') + 2);
	if (ft_strrchr(line, 'z'))
		new->rot.z = ft_atof(ft_strrchr(line, 'z') + 2);
}

t_line			*read_obj(t_line *list, t_object **obj, t_input *data)
{
	t_object	*new;

	if (!(new = (t_object *)malloc(sizeof(t_object))))
		return NULL;
	new->next = NULL;
	while (list && list->line[0] != '}')
	{
		if (ft_strnequ_word(list->line, "pos", 3))
			ft_sort_pos(list->line, new);
		else if (ft_strnequ_word(list->line, "rot", 3))
			ft_sort_rot(list->line, new);
		else if (ft_strnequ_word(list->line, "file", 4))
		{
			if (!(new->file = sort_file(list->line)))
				return (NULL);
			if (!(new->l_file = ft_strjoin("Object/", new->file)))
				return NULL;
			if (!(new->poly = ft_pares_obj(new->l_file, data, new)))
				return (NULL);
		}
		list = list->next;
	}
	push_front_obj(new, obj);
	//printf("OBJ LOAD\n");
	return (list);
}
