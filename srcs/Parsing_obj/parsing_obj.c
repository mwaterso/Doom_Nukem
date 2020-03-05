/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 00:35:11 by beduroul          #+#    #+#             */
/*   Updated: 2020/02/17 00:35:13 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_index		obj_size(t_line *list)
{
	t_index		index;

	index = (t_index){.i = 0, .j = 0, .k = 0};
	while (list)
	{
		if (ft_strnequ_word(list->line, "v ", 2))
			index.i++;
		if (ft_strnequ_word(list->line, "vt ", 3))
			index.j++;
		if (ft_strnequ_word(list->line, "vn ", 3))
			index.k++;
		list = list->next;
	}
	return (index);
}

int			mall_file(t_file_obj *file, t_line *list)
{
	file->size = obj_size(list);
	if (!(file->v = (t_fdot *)malloc(sizeof(t_fdot) * file->size.i)))
		return (0);
	if (!(file->vt = (t_2d *)malloc(sizeof(t_2d) * file->size.j)))
		return (0);
	if (!(file->vn = (t_fdot *)malloc(sizeof(t_fdot) * file->size.k)))
		return (0);
	return (1);
}

int			parse_fobj(t_line *list, t_poly **poly, t_input *d, t_index index)
{
	t_file_obj	file;
	char		*tmp;

	file.lst = NULL;
	if (!(mall_file(&file, list)))
		return (0);
	while (list)
	{
		if (ft_strnequ_word(list->line, "mtllib ", 7))
			sort_mtl(d, list->line, &file);
		if (ft_strnequ_word(list->line, "usemtl ", 7))
			tmp = list->line + 7;
		if (ft_strnequ_word(list->line, "v ", 2))
			sort_tfdot(list->line, &(file.v[index.i++]));
		if (ft_strnequ_word(list->line, "vt ", 3))
			sort_t2d(list->line, &(file.vt[index.j++]));
		if (ft_strnequ_word(list->line, "vn ", 3))
			sort_tfdot(list->line, &(file.vn[index.k++]));
		if (ft_strnequ_word(list->line, "f ", 2))
			sort_poly(list->line + 2, poly, file, tmp);
		list = list->next;
	}
	reverse_p(poly);
	free_file_obj(file);
	return (1);
}

int			p_obj_loop(t_poly **poly, t_input *data, int fd)
{
	t_line		*list;
	int			n_line;
	char		*line;
	int			i;

	i = 0;
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
	if (!(i = parse_fobj(list, poly, data, (t_index){.i = 0, .j = 0, .k = 0})))
		return (0);
	free_line(&list);
	return (i);
}

t_poly		*ft_pares_obj(char *file, t_input *data)
{
	int			fd;
	int			i;
	t_poly		*poly;

	poly = NULL;
	if ((fd = open(file, O_RDONLY)) < 1)
		return (NULL);
	error_file(fd, file);
	if (!(i = p_obj_loop(&poly, data, fd)))
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (poly);
}
