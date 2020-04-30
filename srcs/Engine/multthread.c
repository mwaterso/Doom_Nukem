/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   multthread.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/03/09 17:58:08 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/03/09 18:06:41 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"
void thread_start(t_input	*data, t_2dbox *boxes, int nbrboxes)
{
	int i;
	i = 0;
	while(i < NB_THREAD)
	{
		data->thread_tab[i].i_start = i * (data->win_h * data->win_w / NB_THREAD);
		data->thread_tab[i].i_end = (i + 1) * (data->win_h * data->win_w / NB_THREAD);
		data->thread_tab[i].inputs = data;
        data->thread_tab[i].index = i;
		pthread_create(&data->thread_tab[i].thread, NULL,
		&processbox, &data->thread_tab[i]);
		i++;
	}
    printf("end\n");
	i = 0;
	while (i <= NB_THREAD)
		pthread_join(data->thread_tab[i++].thread, NULL);
}