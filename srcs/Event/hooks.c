/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hooks.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 17:39:51 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 18:07:25 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int	keyboard_move(int key, t_input *inputs)
{
	printf("key  %d\n", key);
	if (key == KEY_UP)
	{
		mapmoveallp(inputs->map, (t_fdot){.x = -0.05, .y = 0, .z = 0});
	}
	if (key == KEY_DOWN)
	{
		mapmoveallp(inputs->map, (t_fdot){.x = 0.05, .y = 0, .z = 0});
	}
	if (key == KEY_RIGHT)
	{
		printf("d\n");
		mapmoveallp(inputs->map, (t_fdot){.x = 0, .y = -0.05, .z = 0});
	}
	if (key == KEY_LEFT)
	{
		mapmoveallp(inputs->map, (t_fdot){.x = 0, .y = 0.05, .z = 0});
	}
	return(1);
}