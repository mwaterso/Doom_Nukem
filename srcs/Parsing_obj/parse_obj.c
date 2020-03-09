/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:25:41 by beduroul          #+#    #+#             */
/*   Updated: 2020/03/04 20:25:42 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		sort_type(char *line, t_object *new)
{
	char	*type;

	if (!(type = sort_file(line)))
		return ;
	if (ft_strcmp(type, "chest") == 0)
		new->type = CHEST;
	else if (ft_strcmp(type, "key") == 0)
		new->type = KEY;
	else if (ft_strcmp(type, "enemi") == 0)
		new->type = ENEMI;
	else if (ft_strcmp(type, "potion") == 0)
		new->type = POTION;
	else if (ft_strcmp(type, "armor") == 0)
		new->type = ARMOR;
	else if (ft_strcmp(type, "munition") == 0)
		new->type = MUN;
	else if (ft_strcmp(type, "scene") == 0)
		new->type = SCEN;
	free(type);
}

void		ft_sort_pos(char *line, t_object *new)
{
	if (ft_strrchr(line, 'x'))
		new->pos.x = ft_atof(ft_strrchr(line, 'x') + 2);
	if (ft_strrchr(line, 'y'))
		new->pos.y = ft_atof(ft_strrchr(line, 'y') + 2);
	if (ft_strrchr(line, 'z'))
		new->pos.z = ft_atof(ft_strrchr(line, 'z') + 2);
}

void		ft_sort_rot(char *line, t_object *new)
{
	if (ft_strrchr(line, 'x'))
		new->rot.x = ft_atof(ft_strrchr(line, 'x') + 2);
	if (ft_strrchr(line, 'y'))
		new->rot.y = ft_atof(ft_strrchr(line, 'y') + 2);
	if (ft_strrchr(line, 'z'))
		new->rot.z = ft_atof(ft_strrchr(line, 'z') + 2);
}

int			loop_read_obj(t_line *list, t_object *new, t_input *data)
{
	if (!(new->file = sort_file(list->line)))
		return (0);
	if (!(new->l_file = ft_strjoin("Object/", new->file)))
		return (0);
	if (!(new->poly = ft_pares_obj(new->l_file, data)))
		return (0);
	return (1);
}

t_line		*read_obj(t_line *list, t_object **obj, t_input *data)
{
	t_object	*new;

	if (!(new = (t_object *)malloc(sizeof(t_object))))
		return (NULL);
	new->next = NULL;
	while (list && list->line[0] != '}')
	{
		loop_read2(list, new);
		if (ft_strnequ_word(list->line, "file", 4))
		{
			if (!(loop_read_obj(list, new, data)))
			{
				free_object(obj, new);
				return (NULL);
			}
		}
		list = list->next;
	}
	ft_strdel(&(new->l_file));
	ft_strdel(&(new->file));
	push_front_obj(new, obj);
	return (list);
}
