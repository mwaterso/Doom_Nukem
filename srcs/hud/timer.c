/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   timer.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/20 16:27:40 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2020/03/05 18:23:52 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "doom.h"

int		cooldown(t_data *data, time_t cd)
{
	struct timeval	timer;
	long			t1;
	long			t2;

	gettimeofday(&timer, NULL);
	t1 = timer.tv_sec * 1000000 + timer.tv_usec;
	t2 = data->timer.save_time.tv_sec * 1000000 +
	data->timer.save_time.tv_usec + cd;
	if (t1 >= t2)
	{
		gettimeofday(&data->timer.save_time, NULL);
		return (1);
	}
	return (0);
}
