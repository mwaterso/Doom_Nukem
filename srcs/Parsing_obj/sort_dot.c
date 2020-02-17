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

t_fdot      sort_tfdot(char *line)
{
    printf("t_fdot = %s\n", line);
    return ((t_fdot){.x = 0, .y = 0, .z = 0});
}

t_2d      sort_t2d(char *line)
{
    printf("t_2d = %s\n", line);
    return ((t_2d){.x = 0, .y = 0});
}
