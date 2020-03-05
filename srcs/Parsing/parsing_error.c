/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 20:24:28 by beduroul          #+#    #+#             */
/*   Updated: 2020/03/02 20:24:31 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		check_texture(t_line *list, int *error)
{
	int			i;
	int			dot;

	i = ft_strnchr(list->line, '=');
	dot = 0;
	if (!i || list->line[i + 1] != ' ' || list->line[i - 1] != ' ')
		poly_error(list, TEX_E, i, error);
	i += 2;
	while (list->line[i])
	{
		if (list->line[i] == '.')
		{
			if (ft_strcmp((list->line + i), ".xpm"))
				poly_error(list, TEX_X, i, error);
			dot = 1;
		}
		else if (!(ft_isalnum(list->line[i])))
			poly_error(list, TEX, i, error);
		i++;
	}
	if (dot != 1)
		poly_error(list, TEX, ft_strlen(list->line), error);
}

static void		error_dot(t_line *list, int *error)
{
	int			i;
	int			count;
	int			len;
	int			tmp;

	len = ft_strlen(list->line);
	i = 0;
	count = 0;
	tmp = 0;
	while (list->line[i++] && i < len)
	{
		if (list->line[i] && list->line[i] == ':')
		{
			inter_cord(list, &tmp, error, &i);
			count++;
		}
	}
	if (count != 5)
		poly_error(list, CORD, ft_strlen(list->line), error);
}

static int		pars_block(t_line *list, int *error, t_index *check)
{
	while (list && list->line[0] != '}')
	{
		if (ft_strnequ_word(list->line, "dot", 3))
		{
			check->j++;
			error_dot(list, error);
		}
		else if (ft_strnequ_word(list->line, "texture", 7))
		{
			check->i++;
			check_texture(list, error);
		}
		else if (list->line[0] != '{' && list->line[0] != '}')
			return (0);
		list = list->next;
	}
	if (!list)
		return (0);
	return (1);
}

static void		line_error(t_line *list, int *error)
{
	t_index		check;

	check = (t_index){.i = 0, .j = 0, .k = 0};
	if (list->line[0] == '{')
	{
		if (!(pars_block(list, error, &check)))
			poly_error(list, BRACKET, 0, error);
		else if ((check.j < 3 || check.j > 4) || check.i != 1)
			poly_error(list, BLOCK, ft_strlen(list->line), error);
	}
	else
		poly_error(list, O_BRACKET, 0, error);
}

int				check_error(t_line *list)
{
	t_line		*tmp;
	int			error;

	tmp = list;
	error = 0;
	if (!list)
		return (0);
	while (tmp)
	{
		if (tmp->next && ft_strnequ_word(tmp->line, "Polygon", 7))
			line_error(tmp->next, &error);
		if (tmp->next && ft_strnequ_word(tmp->line, "Object", 6))
			obj_error(tmp->next, &error);
		tmp = tmp->next;
	}
	if (error > 0)
	{
		ft_putchar('\n');
		ft_putnbr_hexa(error, BOLD | UNDERLINE, 0xF9E79F);
		ft_putstr_hexa(" error founds\n", BOLD | UNDERLINE, 0xF9E79F);
		free_line(&list);
		return (0);
	}
	return (1);
}
