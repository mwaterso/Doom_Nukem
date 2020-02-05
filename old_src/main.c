/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/02 16:48:09 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 17:25:04 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "doom.h"
int		main(int argc, char **argv)
{
	t_input inputs;

	(void)argc;
	inputs.fd = open(argv[1], O_RDONLY);
	inputs.fd2 = open(argv[1], O_RDONLY);
	inputs.fd3 = open(argv[1], O_RDONLY);
	parse_file(&inputs);
	init_var(&inputs);
	return (0);
}