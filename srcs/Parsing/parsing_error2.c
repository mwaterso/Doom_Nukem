/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing_error2.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/26 00:10:19 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 17:43:12 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void	print_block(t_line *list)
{
	while (list->next && list->line[0] != '}')
	{
		if (ft_strnequ_word(list->line, "Polygon", 7))
			break ;
		ft_putnbr_hexa(list->n_line, BOLD, 0x16A085);
		ft_putchar(' ');
		ft_putendl_hexa(list->line, NONE, 0xD5D8DC);
		list = list->next;
	}
}

void print_bracket(t_line *list, int error)
{
	if (error == O_BRACKET)
	{
		ft_putnbr_hexa(list->n_line, BOLD, 0x16A085);
		ft_putchar(' ');
		ft_putendl_hexa("{", BOLD, 0x16A085);
	}
	while (list->next && list->next->line[0] != '}')
	{
		if (ft_strnequ_word(list->line, "Polygon", 7))
			break ;
		ft_putnbr_hexa(list->n_line, BOLD, 0x16A085);
		ft_putchar(' ');
		ft_putendl_hexa(list->line, NONE, 0xD5D8DC);
		list = list->next;
	}
	if (error == BRACKET)
	{
		ft_putnbr_hexa(list->n_line, BOLD, 0x16A085);
		ft_putchar(' ');
		ft_putendl_hexa("}", BOLD, 0x16A085);
	}
}

void		print_error(t_line *list, int error, int i)
{
	ft_putnbr_hexa(list->n_line, BOLD | UNDERLINE, 0xFF6262);
	ft_putstr_hexa("col:", UNDERLINE, 0xEC7063);
	ft_putnbr_hexa(i + 1, BOLD | UNDERLINE, 0xFF6262);
	ft_putstr("\n");
	if (i && error != BLOCK)
	{
		if (error != CORD)
			ft_putendl_hexa(list->line, NONE, 0xD5D8DC);
		else
		{
			ft_putstr_hexa(list->line, NONE, 0xD5D8DC);
			ft_putendl_hexa("~~~~", BOLD, 0x16A085);
		}
		ft_putspace(i);
		ft_putstr_hexa("⬆︎", BOLD, 0x16A085);
	}
	if (error == TEX_X)
		ft_putendl_hexa(" .xpm", BOLD | ITALIC, 0x16A085);
	else if (error == D_OBJ)
		ft_putendl_hexa(" .obj", BOLD | ITALIC, 0x16A085);
	if (error == BRACKET || error == O_BRACKET)
		print_bracket(list, error);
	if (error != BLOCK)
		ft_putchar('\n');
}

void		poly_error(t_line *list, int error, int i, int *err)
{
	if ((*err) > 1)
		ft_putchar('\n');
	if (error == NUM)
	   ft_putstr_hexa("Error invalide value line:", UNDERLINE, 0xEC7063);
	else if (error == TEX || error == TEX_X)
		ft_putstr_hexa("Error invalide name texture line :", UNDERLINE, 0xEC7063);
	else if (error == CORD)
		ft_putstr_hexa("Error wring number cord line :", UNDERLINE, 0xEC7063);
	else if (error == BRACKET || error == O_BRACKET)
		ft_putstr_hexa("Error bad bracket line :", UNDERLINE, 0xEC7063);
	else if (error == TEX_E)
		ft_putstr_hexa("Error bad spacing line :", UNDERLINE, 0xEC7063);
	else if (error == BLOCK)
		ft_putstr_hexa("Error invalide size block line :", UNDERLINE, 0xEC7063);
	else if (error == D_OBJ)
		ft_putstr_hexa("Error invalide name obj file line :", UNDERLINE, 0xEC7063);
	if (list)
		print_error(list, error, i);
	if (error == BLOCK)
		print_block(list);
	(*err)++;
}
