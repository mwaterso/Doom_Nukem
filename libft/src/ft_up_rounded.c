/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_up_rounded.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/30 23:14:54 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 23:15:01 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_up_rounded(double n)
{
	if ((double)(int)n != n)
		n++;
	return ((int)n);
}
