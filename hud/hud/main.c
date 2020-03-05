/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:27:29 by calin             #+#    #+#             */
/*   Updated: 2020/02/20 16:27:32 by calin            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../doom.h"

int		main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	(void)argv;
	init_var(&data);
	if (load_texture_data(&data) == -1)
	{
		ft_putendl("Texture error");
		return (0);
	}
	gettimeofday(&data.timer.save_time, NULL);
	mlx_hook(data.win_addrs, 2, 0, key_press, &data);
	mlx_hook(data.win_addrs, 3, 0, key_release, &data);
	mlx_hook(data.win_addrs, 4, 0, mouse_press, &data);
	mlx_hook(data.win_addrs, 5, 0, mouse_release, &data);
	mlx_loop_hook(data.mlx_addrs, redraw, &data);
	mlx_loop(data.mlx_addrs);
	return (0);
}
