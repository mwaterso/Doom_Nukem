/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_dot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 04:11:14 by beduroul          #+#    #+#             */
/*   Updated: 2020/02/17 04:11:17 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		free_tab(char ***tab)
{
	char	**str;
	int		i;

	i = 0;
	str = *tab;
	while (*str)
	{
		ft_strdel(str);
		i++;
		str = &(*tab)[i];
	}
	ft_memdel((void **)tab);
}

int			sort_tfdot(char *line, t_fdot *dot)
{
	int		i;
	char	**tab;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	if (!(tab = ft_strsplit(line + i, ' ')))
		return (0);
	if (ft_avlen(tab) != 3)
		return (0);
	dot->x = ft_atof(tab[0]);
	dot->y = ft_atof(tab[1]);
	dot->z = ft_atof(tab[2]);
	free_tab(&tab);
	return (1);
}

int			sort_t2d(char *line, t_2d *dot)
{
	int		i;
	char	**tab;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	if (!(tab = ft_strsplit(line + i, ' ')))
		return (0);
	if (ft_avlen(tab) != 2)
		return (0);
	dot->x = ft_atof(tab[0]);
	dot->y = ft_atof(tab[1]);
	free_tab(&tab);
	return (1);
}

int			sort_color(char *line, t_color *color)
{
	int		i;
	char	**tab;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	if (!(tab = ft_strsplit(line + i, ' ')))
		return (0);
	if (ft_avlen(tab) != 3)
		return (0);
	color->r = ft_atof(tab[0]) * 255;
	color->g = ft_atof(tab[1]) * 255;
	color->b = ft_atof(tab[2]) * 255;
	free_tab(&tab);
	return (1);
}
