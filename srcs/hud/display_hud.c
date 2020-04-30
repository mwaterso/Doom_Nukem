/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display_hud.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/20 16:26:26 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2020/03/05 17:57:39 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
/* ************************************************************************** */
#include "doom.h"

void	print_reload(t_data *data)
{
	if (data->total_ammo == 0 && data->current_ammo == 0)
		mlx_string_put(data->mlx_addrs, data->win_addrs, WIN_SIZE_W / 2.3,
		WIN_SIZE_H - 150, 0xFF0000, "Out of ammo !");
	else
		mlx_string_put(data->mlx_addrs, data->win_addrs, WIN_SIZE_W / 2.3,
		WIN_SIZE_H - 150, 0xFF0000, "Press R to reload !");
}

void	print_ammo(t_data *data)
{
	char	*tmpstr;
	char	*str;

	tmpstr = ft_strjoin2(ft_itoa(data->current_ammo), " | ", 1);
	str = ft_strjoin2(tmpstr, ft_itoa(data->total_ammo), 3);
	mlx_string_put(data->mlx_addrs, data->win_addrs, 80, WIN_SIZE_H - 50,
	0xFFFFFF, str);
	ft_strdel(&str);
}

int		print_menu(t_data *data)
{
	int i;

	i = -1;
	while (++i < 4)
		mlx_put_image_to_window(data->mlx_addrs, data->win_addrs,
		data->menu_texture[i].img.ad, data->menu_texture[i].pos_text.x,
		data->menu_texture[i].pos_text.y);
	return (0);
}

void	print_inventory(t_data *data)
{
	char	*str;
	char	*tmp;

	if (data->inventory.slot_one != 0)
	{
		str = ft_itoa(data->inventory.slot_one);
		mlx_string_put(data->mlx_addrs, data->win_addrs, 648, WIN_SIZE_H - 70,
		0xFFFFFF, (tmp = ft_strjoin2("x", str, 2)));
		mlx_put_image_to_window(data->mlx_addrs, data->win_addrs,
		data->tab_tex[9].img.ad, data->pos_texture[9].x,
		data->pos_texture[9].y);
		ft_strdel(&tmp);
	}
	if (data->inventory.slot_two != 0)
	{
		str = ft_itoa(data->inventory.slot_two);
		mlx_string_put(data->mlx_addrs, data->win_addrs, 750, WIN_SIZE_H - 70,
		0xFFFFFF, (tmp = ft_strjoin2("x", str, 2)));
		mlx_put_image_to_window(data->mlx_addrs, data->win_addrs,
		data->tab_tex[10].img.ad, data->pos_texture[10].x,
		data->pos_texture[10].y);
		ft_strdel(&tmp);
	}
}

int		print_hud(t_data *data)
{
	int i;
	int	text_to_print;

	text_to_print = NB_HUD_TEX - NB_ANIM_TEX - 2;
	if (data->menu_state == 1)
	{
		print_menu(data);
		return (0);
	}
	health(data);
	shield(data);
	print_inventory(data);
	i = -1;
	while (++i < text_to_print)
		mlx_put_image_to_window(data->mlx_addrs, data->win_addrs,
		data->tab_tex[i].img.ad, data->pos_texture[i].x,
		data->pos_texture[i].y);
	print_ammo(data);
	return (0);
}
