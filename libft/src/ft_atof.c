/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atof.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 18:10:25 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/27 18:10:26 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

float           ft_atof(const char *str)
{
    float   res;
    float   res2;
    char    *c;
    int     len;
    c = (char *)str;
    res = (float)ft_atoi(c);
    while (*c && *c != '.')
        c++;
    if (*c == '.')
        c++;
    res2 = (float)ft_atoi(c);
    len = ft_strlen(c);
    while (len--)
        res2 /= 10;
    return (res + ((*str == '-') ? -res2 : res2));
}
