/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display_weapon.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/20 16:26:37 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2020/03/05 18:23:39 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

// void	init_var(t_data *data)
// {
// 	data->inventory = (t_inventory){.slot_one = 7, .slot_two = 8,
// 	.slot_three = 1, .slot_four = 0};
// 	data->health_bar = (t_life){.x_min = 1400, .x_max = 1556, .y_min = 813,
// 	.y_max = 831, .health = 20, .shield = 0};
// 	data->current_ammo = 30;
// 	data->total_ammo = 256;
// 	data->healanim.index_heal_anim = -1;
// 	data->shieldanim.index_shield_anim = -1;
// 	data->weaponanim.index_wpn_anim = -1;
// 	data->weaponanim.index_rld_anim = -1;
// 	data->menu_state = 1;
// 	data->first_frame = 0;
// }

void	reload_animation(t_data *data)
{
	mlx_destroy_image(data->mlx_addrs, data->tab_tex[0].img.ad);
	if (data->weaponanim.index_rld_anim == 0)
		data->name_texture[0] = "srcs/hud/images/rld.xpm";
	if (data->weaponanim.index_rld_anim == 1)
		data->name_texture[0] = "srcs/hud/images/rld1.xpm";
	if (data->weaponanim.index_rld_anim == 2)
		data->name_texture[0] = "srcs/hud/images/rld2.xpm";
	if (data->weaponanim.index_rld_anim == 3)
		data->name_texture[0] = "srcs/hud/images/wpn3.xpm";
	data->tab_tex[0].img.ad = mlx_xpm_file_to_image(data->mlx_addrs,
	data->name_texture[0], &data->tab_tex[0].width, &data->tab_tex[0].height);
	data->tab_tex[0].img.tab =
	(int *)mlx_get_data_addr(data->tab_tex[0].img.ad,
	&(data->tab_tex[0].img.bits_per_pixel), &(data->tab_tex[0].img.size_line),
	&(data->tab_tex[0].img.endian));
	mlx_put_image_to_window(data->mlx_addrs, data->win_addrs,
	data->tab_tex[0].img.ad, 1000, 500);
	if (cooldown(data, 60000))
		data->weaponanim.index_rld_anim++;
	if (data->weaponanim.index_rld_anim == 4)
		data->weaponanim.index_rld_anim = -1;
}

void	weapon_animation(t_data *data)
{
	mlx_destroy_image(data->mlx_addrs, data->tab_tex[0].img.ad);
	if (data->weaponanim.index_wpn_anim == 0)
		data->name_texture[0] = "srcs/hud/images/wpn7.xpm";
	if (data->weaponanim.index_wpn_anim == 1)
		data->name_texture[0] = "srcs/hud/images/wpn6.xpm";
	if (data->weaponanim.index_wpn_anim == 2)
		data->name_texture[0] = "srcs/hud/images/wpn5.xpm";
	if (data->weaponanim.index_wpn_anim == 3)
		data->name_texture[0] = "srcs/hud/images/wpn4.xpm";
	if (data->weaponanim.index_wpn_anim == 4)
		data->name_texture[0] = "srcs/hud/images/wpn3.xpm";
	if (data->weaponanim.index_wpn_anim == 5)
		data->name_texture[0] = "srcs/hud/images/wpn2.xpm";
	data->tab_tex[0].img.ad = mlx_xpm_file_to_image(data->mlx_addrs,
	data->name_texture[0], &data->tab_tex[0].width, &data->tab_tex[0].height);
	data->tab_tex[0].img.tab =
	(int *)mlx_get_data_addr(data->tab_tex[0].img.ad,
	&(data->tab_tex[0].img.bits_per_pixel), &(data->tab_tex[0].img.size_line),
	&(data->tab_tex[0].img.endian));
	mlx_put_image_to_window(data->mlx_addrs, data->win_addrs,
	data->tab_tex[0].img.ad, 1000, 500);
	if (cooldown(data, 30000))
		data->weaponanim.index_wpn_anim++;
	if (data->weaponanim.index_wpn_anim == 5)
		data->weaponanim.index_wpn_anim = -1;
}

int		ammo(t_data *data)
{
	int	charger;

	if (data->total_ammo == 0)
	{
		print_reload(data);
		return (0);
	}
	charger = 30 - data->current_ammo;
	if (data->total_ammo - charger < 0)
		charger = data->total_ammo;
	data->total_ammo = (data->total_ammo - charger > 0) ?
	data->total_ammo - charger : 0;
	data->current_ammo += charger;
	return (0);
}
