/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putstr_hexa.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 18:45:17 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 18:45:22 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

void       ft_putstr_hexa(char *str, t_putstr_style type, uint32_t color)
{
    if (type & UNDERLINE)
        ft_putstr("\033[4m");
    if (type & ITALIC)
        ft_putstr("\033[3m");
    if (type & BOLD)
        ft_putstr("\033[1m");
    ft_putstr("\033[38;2;");
	ft_putnbr((color >> 16) & 0xFF);
	ft_putchar(';');
	ft_putnbr((color >> 8) & 0xFF);
	ft_putchar(';');
	ft_putnbr((color) & 0xFF);
	ft_putchar('m');
    ft_putstr(str);
    ft_putstr("\033[0m");
}
