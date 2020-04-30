/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_function.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/20 16:28:32 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2020/03/05 18:24:03 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int		heal_texture_animation(t_data *data)
{
	int i;

	data->healanim.tab_texture[0] = "srcs/hud/images/healanim1.xpm";
	data->healanim.tab_texture[1] = "srcs/hud/images/healanim2.xpm";
	data->healanim.tab_texture[2] = "srcs/hud/images/healanim3.xpm";
	data->healanim.tab_texture[3] = "srcs/hud/images/healanim4.xpm";
	i = -1;
	while (++i < NB_ANIM_TEX)
	{
		if (!(data->healanim.anim_texture[i].img.ad =
		mlx_xpm_file_to_image(data->mlx_addrs, data->healanim.tab_texture[i],
		&data->healanim.anim_texture[i].width,
		&data->healanim.anim_texture[i].height)))
			return (-1);
		data->healanim.anim_texture[i].img.tab =
		(int *)mlx_get_data_addr(data->healanim.anim_texture[i].img.ad,
		&(data->healanim.anim_texture[i].img.bits_per_pixel),
		&(data->healanim.anim_texture[i].img.size_line),
		&(data->healanim.anim_texture[i].img.endian));
	}
	return (0);
}

int		load_menu_texture(t_data *data)
{
	int i;

	data->menu_texture[0].name_text = "srcs/hud/images/bg_menu.xpm";
	data->menu_texture[0].pos_text = (t_dot){.x = 0, .y = 0};
	data->menu_texture[1].name_text = "srcs/hud/images/play.xpm";
	data->menu_texture[1].pos_text = (t_dot){.x = 600, .y = 400};
	data->menu_texture[2].name_text = "srcs/hud/images/editor.xpm";
	data->menu_texture[2].pos_text = (t_dot){.x = 600, .y = 550};
	data->menu_texture[3].name_text = "srcs/hud/images/exit.xpm";
	data->menu_texture[3].pos_text = (t_dot){.x = 600, .y = 700};
	data->menu_state = 1;
	i = -1;
	while (++i < 4)
	{
		if (!(data->menu_texture[i].img.ad =
		mlx_xpm_file_to_image(data->mlx_addrs, data->menu_texture[i].name_text,
		&data->menu_texture[i].width, &data->menu_texture[i].height)))
			return (-1);
		data->menu_texture[i].img.tab =
		(int *)mlx_get_data_addr(data->menu_texture[i].img.ad,
		&(data->menu_texture[i].img.bits_per_pixel),
		&(data->menu_texture[i].img.size_line),
		&(data->menu_texture[i].img.endian));
	}
	return (0);
}

int		shield_texture_animation(t_data *data)
{
	int i;

	data->shieldanim.tab_texture[0] = "srcs/hud/images/shieldanim1.xpm";
	data->shieldanim.tab_texture[1] = "srcs/hud/images/shieldanim2.xpm";
	data->shieldanim.tab_texture[2] = "srcs/hud/images/shieldanim3.xpm";
	data->shieldanim.tab_texture[3] = "srcs/hud/images/shieldanim4.xpm";
	i = -1;
	while (++i < NB_ANIM_TEX)
	{
		if (!(data->shieldanim.anim_texture[i].img.ad =
		mlx_xpm_file_to_image(data->mlx_addrs, data->shieldanim.tab_texture[i],
		&data->shieldanim.anim_texture[i].width,
		&data->shieldanim.anim_texture[i].height)))
			return (-1);
		data->shieldanim.anim_texture[i].img.tab =
		(int *)mlx_get_data_addr(data->shieldanim.anim_texture[i].img.ad,
		&(data->shieldanim.anim_texture[i].img.bits_per_pixel),
		&(data->shieldanim.anim_texture[i].img.size_line),
		&(data->shieldanim.anim_texture[i].img.endian));
	}
	return (0);
}

void	fill_texture_half_tab(t_data *data)
{
	data->name_texture[7] = "srcs/hud/images/inv.xpm";
	data->pos_texture[7] = (t_dot){.x = WIN_SIZE_W / 1.77,
	.y = WIN_SIZE_H - 80};
	data->name_texture[8] = "srcs/hud/images/ammo.xpm";
	data->pos_texture[8] = (t_dot){.x = 10, .y = WIN_SIZE_H - 85};
	data->name_texture[9] = "srcs/hud/images/shield_pots.xpm";
	data->pos_texture[9] = (t_dot){.x = 615, .y = WIN_SIZE_H - 70};
	data->name_texture[10] = "srcs/hud/images/heal_pots.xpm";
	data->pos_texture[10] = (t_dot){.x = 712, .y = WIN_SIZE_H - 72};
}

void	fill_texture_tab(t_data *data)
{
	data->name_texture[0] = "srcs/hud/images/wpn.xpm";
	data->pos_texture[0] = (t_dot){.x = 1000, .y = 500};
	data->name_texture[1] = "srcs/hud/images/hpbar.xpm";
	data->pos_texture[1] = (t_dot){.x = WIN_SIZE_W - 235,
	.y = WIN_SIZE_H - 110};
	data->name_texture[2] = "srcs/hud/images/hpbar.xpm";
	data->pos_texture[2] = (t_dot){.x = WIN_SIZE_W - 235, .y = WIN_SIZE_H - 55};
	data->name_texture[3] = "srcs/hud/images/shield.xpm";
	data->pos_texture[3] = (t_dot){.x = WIN_SIZE_W - 234, .y = WIN_SIZE_H - 55};
	data->name_texture[4] = "srcs/hud/images/inv.xpm";
	data->pos_texture[4] = (t_dot){.x = WIN_SIZE_W / 2, .y = WIN_SIZE_H - 80};
	data->name_texture[5] = "srcs/hud/images/inv.xpm";
	data->pos_texture[5] = (t_dot){.x = WIN_SIZE_W / 2.3, .y = WIN_SIZE_H - 80};
	data->name_texture[6] = "srcs/hud/images/inv.xpm";
	data->pos_texture[6] = (t_dot){.x = WIN_SIZE_W / 2.7, .y = WIN_SIZE_H - 80};
	fill_texture_half_tab(data);
}
