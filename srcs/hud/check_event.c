/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_event.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/20 16:26:11 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2020/03/06 19:30:52 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int		check_inputs(t_data *data)
{
	if (data->health_bar.health == 0)
	{
		dead_anim(data);
		return (0);
	}
	if ((data->keycode.r == 1 && data->current_ammo != 30) ||
	data->current_ammo == 0)
	{
		if (data->weaponanim.index_rld_anim == -1)
			data->weaponanim.index_rld_anim = 0;
		ammo(data);
	}
	return (1);
}

void	check_inputs_bis(t_data *data)
{
	if (data->keycode.t == 1)
	{
		if (data->health_bar.shield > 0)
			data->health_bar.shield -= 10;
		else if (data->health_bar.health > 0)
			data->health_bar.health -= 10;
	}
	if (data->keycode.one == 1 && (data->inventory.slot_one > 0 &&
	data->health_bar.shield < 100) && cooldown(data, 300000))
	{
		if (data->shieldanim.index_shield_anim == -1)
			data->shieldanim.index_shield_anim = 0;
		data->inventory.slot_one--;
		data->health_bar.shield += 10;
	}
	if (data->keycode.two == 1 && (data->inventory.slot_two > 0 &&
	data->health_bar.health < 100) && cooldown(data, 300000))
	{
		if (data->healanim.index_heal_anim == -1)
			data->healanim.index_heal_anim = 0;
		data->inventory.slot_two--;
		data->health_bar.health += 10;
	}
}

void	check_anim(t_data *data)
{
	if (data->healanim.index_heal_anim != -1)
		heal_animation(data);
	if (data->shieldanim.index_shield_anim != -1)
		shield_animation(data);
	if (data->weaponanim.index_wpn_anim != -1 && data->current_ammo > 0)
		weapon_animation(data);
	if (data->weaponanim.index_rld_anim != -1 &&
	data->weaponanim.index_wpn_anim == -1)
		reload_animation(data);
}

void		check_fire(t_data *data)
{
	//printf("fdsfsd\n");
	if (data->current_ammo == 0)
		print_reload(data);
	else if (data->weaponanim.index_wpn_anim == -1)
		data->weaponanim.index_wpn_anim = 0;
	data->current_ammo--;
}
