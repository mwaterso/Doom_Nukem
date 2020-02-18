/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_poly.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 00:11:13 by beduroul          #+#    #+#             */
/*   Updated: 2020/02/18 00:11:15 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_poly         *init_pol(t_file_obj file, t_poly *new, char **tab)
{
    char    **split;
    t_index index;

    index = (t_index){.i = -1, .j = 0, .k = 0};
    split = NULL;
    ft_bzero(new->dot, sizeof(new->dot));
    ft_bzero(new->dot_vn, sizeof(new->dot_vn));
    ft_bzero(new->cord, sizeof(new->cord));
    while (tab[++(index.i)])
    {
        if (!(split = ft_strsplit(tab[index.i], '/')))
           return NULL;
        new->dot[index.j] = file.v[ft_atoi(split[0]) - 1];
        new->cord[index.j] = file.vt[ft_atoi(split[1]) - 1];
        new->dot_vn[index.j] = file.vn[ft_atoi(split[2]) - 1];
        index.j++;
    }
    //free_tab(&tab);
    print_parse1(new);/*---------------A VIREE----------------*/
    return new;
}

int         sort_poly(char *line, t_poly **poly, t_file_obj file)
{
    char **tab;
    t_poly *new;

    new = NULL;
    if (!(new = (t_poly *)malloc(sizeof(t_poly))))
        return 0;
    if (!(tab = ft_strsplit(line, ' ')))
        return 0;
    if (!(new = init_pol(file, new, tab)))
      return (0);
    (void)poly, (void)file;
    free_tab(&tab);
    push_front_pol(new, poly);
    return 1;
}
