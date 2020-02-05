/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   first_word.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 18:13:47 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/09 18:13:49 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_strnequ_word(char const *s1, char const *s2, size_t n)
{
	int		i;
	int		len;

	if (!s1 || !s2)
		return (0);
	i = 0;
	len = ft_strlen(s1);
	while (s1[i] != s2[0] && i < len)
		i++;
	if (i >= len)
		return (0);
	return (!ft_strncmp(s1 + i, s2, n));
}
