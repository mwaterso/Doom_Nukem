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

t_index    obj_size(t_line *list)
{
	t_index index;

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

int     mall_file(t_file_obj *file, t_line *list)
{
	t_index i;

	i = obj_size(list);
	if (!(file->v = (t_fdot *)malloc(sizeof(t_fdot) * i.i + 1)))
		return 0;
	if (!(file->vt = (t_2d *)malloc(sizeof(t_2d) * i.j + 1)))
		return 0;
	if (!(file->vn = (t_fdot *)malloc(sizeof(t_fdot) * i.k + 1)))
		return 0;
	return 1;
}

int     parse_file_obj(t_line *list, t_poly **poly, t_input *data)
{
	t_file_obj  file;
	t_index     index;

	index = (t_index){.i = 0, .j = 0, .k = 0};
	if (!(mall_file(&file, list)))
		return 0;
   while (list)
   {
		if (ft_strnequ_word(list->line, "v ", 2))
			file.v[index.i++] = sort_tfdot(list->line);
		if (ft_strnequ_word(list->line, "vt ", 3))
		   file.vt[index.j++] = sort_t2d(list->line);
		if (ft_strnequ_word(list->line, "vn ", 3))
           file.vn[index.k++] = sort_tfdot(list->line);
		list = list->next;
   }
   (void)data, (void)poly;
   return 1;
}

int     p_obj_loop(t_poly **poly, t_input *data, int fd)
{
	t_line *list;
	int n_line;
	char *line;
	int i;

	i = 0;
	n_line = 0;
	list = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if(!(creat_elem_l(line, n_line, &list)))
			return 0;
		n_line++;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (!(i = parse_file_obj(list, poly, data)))
		return (0);
	return i;
}

t_poly *ft_pares_obj(char *file, t_input *data)
{
	int		fd;
	int 	i;
	t_poly	*poly;

	(void)data;
	(void)i;
	poly = NULL;
	if ((fd = open(file, O_RDONLY)) < 1)
		return (NULL);
	error_file(fd, file);
	if (!(i = p_obj_loop(&poly, data, fd)))
		return (NULL);
	close(fd);
	return NULL;
}
