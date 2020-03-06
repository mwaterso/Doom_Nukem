/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_poly.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 19:37:37 by beduroul          #+#    #+#             */
/*   Updated: 2020/03/02 19:37:44 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

char		*sort_file(char *line)
{
	int			i;
	int			tmp;
	char		*str;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	tmp = i += 2;
	while (line[tmp] && !ft_ispace(line[tmp]))
		tmp++;
	if (!(str = (char *)malloc(sizeof(char) * tmp + 1)))
		return (NULL);
	tmp = 0;
	while (line[i] && !ft_ispace(line[i]))
	{
		str[tmp] = line[i];
		tmp++;
		i++;
	}
	str[tmp] = '\0';
	return (str);
}

t_line		*poly_read(t_line *list, t_poly **poly)
{
	t_index		index;
	t_poly		*new;
	int			dot;

	dot = 0;
	index = (t_index){.i = -1, .j = 0, .k = 0};
	if (!(new = (t_poly *)malloc(sizeof(t_poly))))
		return (NULL);
	new->next = NULL;
	new->nbr_p = 4;
	while (list && list->line[0] != '}')
	{
		if (ft_strnequ_word(list->line, "dot", 3))
		{
			sort_dot(list->line, new, &index);
			dot++;
		}
		else if (ft_strnequ_word(list->line, "texture", 7))
			if (!(new->tex = sort_file(list->line)))
				return (NULL);
		list = list->next;
	}
	dot < 4 ? new->nbr_p = dot : 0;
	push_front_pol(new, poly);
	return (list);
}

int			parse_file(t_line *list, t_poly **poly, t_input *data)
{
	int			count;
	t_line		*tmp;

	tmp = list;
	count = 0;
	if (!(check_error(list)))
		return (0);
	data->obj = NULL;
	while (tmp)
	{
		if (ft_strnequ_word(tmp->line, "//Polygon", 9) ||
		ft_strnequ_word(tmp->line, "//Object", 8))
			tmp = tmp->next;
		else if (!(loop_read(tmp, &count, poly, data)))
			return (0);
		tmp = tmp->next;
	}
	reverse_p(poly);
	reverse_o(&(data->obj));
	return (count);
}

t_poly		*parsing_poly(char *file, t_input *data)
{
	int			fd;
	int			i;
	t_line		*list;
	t_poly		*poly;

	poly = NULL;
	list = NULL;
	if ((fd = open(file, O_RDONLY)) < 1)
		return (NULL);
	if (!(read(fd, NULL, 1)))
		return (NULL);
	error_file(fd, file);
	if (!(i = parse_loop(&poly, list, data, fd)))
	{
		free_poly(&poly);
		free_line(&list);
		return (NULL);
	}
	print_s(i);
	close(fd);
	return (poly);
}
