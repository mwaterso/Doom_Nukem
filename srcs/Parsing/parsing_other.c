/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:14:38 by beduroul          #+#    #+#             */
/*   Updated: 2020/02/27 17:14:40 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			sort_dot(char *line, t_poly *new, t_index *index)
{
	if (ft_strrchr(line, 'x'))
		new->dot[index->j].x = ft_atof(ft_strrchr(line, 'x') + 2);
	if (ft_strrchr(line, 'y'))
		new->dot[index->j].y = ft_atof(ft_strrchr(line, 'y') + 2);
	if (ft_strrchr(line, 'z'))
		new->dot[index->j++].z = ft_atof(ft_strrchr(line, 'z') + 2);
	if (ft_strrchr(line, 'X'))
		new->cord[index->k].x = ft_atof(ft_strrchr(line, 'X') + 2);
	if (ft_strrchr(line, 'Y'))
		new->cord[index->k++].y = ft_atof(ft_strrchr(line, 'Y') + 2);
	if (*(ft_strrchr(line, 'x') + 2) == 'X')
		new->nbr_p--;
	if (*(ft_strrchr(line, 'y') + 2) == 'X')
		new->nbr_p--;
	else if (*(ft_strrchr(line, 'z') + 2) == 'X')
		new->nbr_p--;
	return (1);
}

int			loop_read(t_line *tmp, int *count, t_poly **poly, t_input *data)
{
	if (ft_strnequ_word(tmp->line, "Polygon", 7))
	{
		(*count)++;
		if (!(tmp = poly_read(tmp, poly)))
			return (0);
	}
	else if (ft_strnequ_word(tmp->line, "Object", 6))
		if (!(tmp = read_obj(tmp, &(data->obj), data)))
			return (0);
	return (1);
}

int			gnl_poly(int fd, t_line **list)
{
	char	*line;
	int		n_line;

	n_line = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(creat_elem_l(line, n_line, list)))
			return (0);
		n_line++;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	reverse_l(list);
	return (1);
}

int			parse_loop(t_poly **poly, t_line *list, t_input *data, int fd)
{
	int		i;

	i = 0;
	if (!(gnl_poly(fd, &list)))
	{
		printf("COUOCUO\n");
		return (0);
	}
	if (!(i = parse_file(list, poly, data)))
	{
		free_line(&list);
		return (0);
	}
	if (!(load_tex(poly, data)))
	{
		free(&list);
		write(1, "load tex fail\n", 14);
		return (0);
	}
	free_line(&list);
	return (i);
}

void		print_s(int i)
{
	ft_putstr_hexa("parsing sucsess : ", BOLD | UNDERLINE, 0x4DA6D9);
	ft_putnbr_hexa(i, BOLD | UNDERLINE, 0x4EEFD2);
	ft_putendl_hexa(" loaded", BOLD | UNDERLINE, 0x4DA6D9);
}
