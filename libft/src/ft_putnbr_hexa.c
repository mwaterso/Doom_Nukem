/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_hexa.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 18:50:54 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 18:50:56 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

void       ft_putnbr_hexa(int nbr, t_putstr_style type, uint32_t color)
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
    ft_putnbr(nbr);
    ft_putstr("\033[0m");
}
