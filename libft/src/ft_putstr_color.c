/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putstr_color.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 21:48:20 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 21:48:23 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putstr_color(const char *s, const char *color)
{
	ft_putstr(color);
	ft_putstr(s);
	ft_putstr("\e[39;49m");
}
