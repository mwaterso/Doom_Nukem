/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   color_txt.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 18:22:39 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 18:22:41 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

char	*color_txt(char *str, char *name, char *color)
{
	ft_strcat(str, color);
	ft_strcat(str, name);
	ft_strcat(str, "\e[39;49m");
	return (str);
}
