/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:26:48 by calin             #+#    #+#             */
/*   Updated: 2020/02/20 16:26:50 by calin            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../doom.h"

int		mouse_release(int button, int x, int y, void *param)
{
	t_data *data;

	data = (t_data *)param;
	(void)x;
	(void)y;
	if (y > 0)
	{
		if (button == 1)
			data->keycode.l_click = 0;
	}
	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (x > 625 && x < 915 && y > 425 && y < 525)
		data->menu_state = 0;
	if (data->menu_state == 1 && (x > 625 && x < 915 && y > 576 && y < 671))
		printf("Exec editor\n");
	if (data->menu_state == 1 && (x > 625 && x < 915 && y > 727 && y < 822))
		close_game(data);
	if (y > 0)
	{
		if (button == 1)
			data->keycode.l_click = 1;
	}
	return (0);
}

int		key_release(int keycode, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keycode == 15)
		data->keycode.r = 0;
	if (keycode == 17)
		data->keycode.t = 0;
	if (keycode == 18)
		data->keycode.one = 0;
	if (keycode == 19)
		data->keycode.two = 0;
	if (keycode == 53)
		data->keycode.escape = 0;
	return (0);
}

int		key_press(int keycode, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keycode == 15)
		data->keycode.r = 1;
	if (keycode == 17)
		data->keycode.t = 1;
	if (keycode == 18)
		data->keycode.one = 1;
	if (keycode == 19)
		data->keycode.two = 1;
	if (keycode == 53)
		close_game(data);
	return (0);
}

int		redraw(void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (data->menu_state != 1)
	{
		if (check_inputs(data) == 0)
			return (0);
		check_inputs_bis(data);
		if (data->keycode.l_click == 1 && cooldown(data, 150000)
		&& data->first_frame == 1)
			return (check_fire(data));
		data->first_frame = 1;
	}
	mlx_clear_window(data->mlx_addrs, data->win_addrs);
	check_anim(data);
	print_hud(data);
	return (0);
}
