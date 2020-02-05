/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_2dstrdel.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/21 20:01:35 by aducimet     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 18:27:19 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_2dstrdel(char ***as)
{
	int		i;

	i = 0;
	if (*as)
	{
		while ((*as)[i])
			ft_strdel(&(*as)[i++]);
		free(*as);
		*as = NULL;
	}
}