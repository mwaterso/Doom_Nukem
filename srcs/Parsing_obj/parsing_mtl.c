/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mtl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:02:20 by beduroul          #+#    #+#             */
/*   Updated: 2020/02/18 20:02:21 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		sort_mtllib(char *line, t_mtl *mlt, t_input *data)
{
	int			i;
	char		*file;

	i = -1;
	while (line[++i])
		if (line[i] == ' ')
			break ;
	if (!(file = ft_strjoin("Object/", line + (i + 1))))
		return ;
	if (!(mlt->tex.tab = mlx_xpm_file_to_image(data->mlx_ad, file,
		&mlt->tex.width, &mlt->tex.height)))
		return ;
	if (!(mlt->tex.img = (unsigned int *)mlx_get_data_addr(mlt->tex.tab,
		&(mlt->tex.bpp), &(mlt->tex.s_l), &(mlt->tex.endian))))
		return ;
	ft_strdel(&file);
}

t_line		*parse_mtl(t_input *data, t_line *list, t_file_obj *file)
{
	t_lst_mtl	*new;

	if (!(new = (t_lst_mtl *)malloc(sizeof(t_lst_mtl))))
		return (0);
	new->next = NULL;
	while (list && ft_strcmp(list->line, "\n") > 0)
	{
		if (ft_strnequ_word(list->line, "Ka ", 3))
			sort_color(list->line, &(new->mtl.ka));
		if (ft_strnequ_word(list->line, "Kd ", 3) &&
		ft_isdigit((*list->line + 3)))
			sort_color(list->line, &(new->mtl.kd));
		if (ft_strnequ_word(list->line, "map_Kd ", 7))
			sort_mtllib(list->line, &(new->mtl), data);
		if (ft_strnequ_word(list->line, "newmtl ", 7))
			if (!(new->name = sort_material(list->line)))
				return (NULL);
		list = list->next;
	}
	push_front_mtl(new, &(file->lst));
	return (list);
}

void		check_newmtl(t_line *list, t_input *data, t_file_obj *file)
{
	while (list)
	{
		if (ft_strnequ_word(list->line, "newmtl ", 7))
			if (!(list = parse_mtl(data, list, file)))
				break ;
		list = list->next;
	}
}

int			p_mtl_loop(t_input *data, int fd, t_file_obj *file)
{
	t_line		*list;
	int			n_line;
	char		*line;

	n_line = 0;
	list = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(creat_elem_l(line, n_line, &list)))
			return (0);
		n_line++;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	reverse_l(&list);
	check_newmtl(list, data, file);
	free_line(&list);
	return (1);
}

void		sort_mtl(t_input *data, char *file, t_file_obj *f)
{
	int			fd;
	int			i;
	char		*l_file;

	i = -1;
	while (file[++i])
		if (file[i] == ' ')
			break ;
	if (!(l_file = ft_strjoin("Object/", file + (i + 1))))
		return ;
	if ((fd = open(l_file, O_RDONLY)) < 1)
		return ;
	error_file(fd, file);
	if (!(p_mtl_loop(data, fd, f)))
		return ;
	ft_strdel(&l_file);
}
