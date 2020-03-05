/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 00:03:44 by beduroul          #+#    #+#             */
/*   Updated: 2020/02/17 00:03:46 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		check_file(t_line *list, int *error)
{
	int i;
	int dot;

	i = ft_strnchr(list->line, '=');
	dot = 0;
	if (!i || list->line[i + 1] != ' ' || list->line[i - 1] != ' ')
		poly_error(list, TEX_E, i, error);
	i += 2;
	while (list->line[i])
	{
		if (list->line[i] == '.')
		{
			if (ft_strcmp((list->line + i), ".obj"))
				poly_error(list, D_OBJ, i, error);
			dot = 1;
		}
		else if (!(ft_isalnum(list->line[i])))
			poly_error(list, TEX, i, error);
		i++;
	}
	if (dot != 1)
		poly_error(list, TEX, ft_strlen(list->line), error);
}

void			loop_err_obj(t_line *list, int *tmp, int *i, int *error)
{
	if (list->line[*i - 1] != 'x' && list->line[*i - 1] != 'y' &&
	list->line[*i - 1] != 'z')
		poly_error(list, NUM, *i, error);
	*tmp = *i;
	while (list->line[++(*i)] && list->line[*i] != ',')
		if (list->line[*i] != '-' && list->line[*i] != '.' &&
		!ft_isdigit(list->line[*i]))
		{
			poly_error(list, NUM, *i, error);
			break ;
		}
	if (*tmp + 1 == *i)
		poly_error(list, NUM, *i, error);
}

void			error_dot_obj(t_line *list, int *error)
{
	int i;
	int count;
	int len;
	int tmp;

	len = ft_strlen(list->line);
	i = 0;
	count = 0;
	tmp = 0;
	while (list->line[i++] && i < len)
	{
		if (list->line[i] && list->line[i] == ':')
		{
			loop_err_obj(list, &tmp, &i, error);
			count++;
		}
	}
	if (count != 3)
		poly_error(list, CORD, ft_strlen(list->line), error);
}

int				obj_block(t_line *list, int *error, t_index *check)
{
	while (list && list->line[0] != '}')
	{
		if (ft_strnequ_word(list->line, "rot", 3))
		{
			check->i++;
			error_dot_obj(list, error);
		}
		else if (ft_strnequ_word(list->line, "pos", 3))
		{
			check->j++;
			error_dot_obj(list, error);
		}
		else if (ft_strnequ_word(list->line, "file", 4))
		{
			check->k++;
			check_file(list, error);
		}
		else if (list->line[0] != '{' && list->line[0] != '}' &&
		!ft_strnequ_word(list->line, "type", 4))
			return (0);
		list = list->next;
	}
	if (!list)
		return (0);
	return (1);
}

void			obj_error(t_line *list, int *error)
{
	t_index index;

	index = (t_index){.i = 0, .j = 0, .k = 0};
	if (list->line[0] == '{')
	{
		if (!(obj_block(list, error, &index)))
			poly_error(list, BRACKET, 0, error);
		else if (index.i != 1 && index.j != 1 && index.k != 1)
			poly_error(list, BLOCK, ft_strlen(list->line), error);
	}
	else
		poly_error(list, O_BRACKET, 0, error);
}
