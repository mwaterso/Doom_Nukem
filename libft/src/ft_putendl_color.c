/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putendl_color.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 18:26:10 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 18:26:11 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putendl_color(const char *s, const char *color)
{
	ft_putstr(color);
	ft_putstr(s);
	ft_putendl("\e[39;49m");
}
