/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/20 16:26:48 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2020/03/09 17:39:18 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "doom.h"

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
	t_input *data;

	data = (t_input *)param;
	data->data_hud->keys[keycode] = 0;
	return (0);
}

int		key_press(int keycode, void *param)
{
	t_input *data;

	data = (t_input *)param;
	data->data_hud->keys[keycode] = 1;
	if (keycode == 53)
		close_game(data->data_hud);
	return (0);
}
void check_hooks3(t_input *inputs, int key)
{
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_RIGHT || key == KEY_LEFT)
		moove(inputs, key);
	else if (key == KEY_J)
		inputs->debug = (inputs->debug ? 0 : 1);
	else if (key == KEY_W)
		inputs->angley += ROTY;
	else if (key == KEY_S)
		inputs->angley -= ROTY;
	else if (key == KEY_A)
		maprotateallp(inputs->map, (t_fdot){.x = 0, .y = 0, .z = -1}, inputs);
	else if (key == KEY_D)
		maprotateallp(inputs->map, (t_fdot){.x = 0, .y = 0, .z = 1}, inputs);
}

void	check_mouse(t_input *input)
{
	if (input->data_hud->keycode.l_click == 1 && cooldown(input->data_hud, 150000)
	&& input->data_hud->first_frame == 1)
		check_fire(input->data_hud);
}

void check_hooks2(t_input *input, int key)
{	
	if (key == KEY_1 && (input->data_hud->inventory.slot_one > 0 &&
	input->data_hud->health_bar.shield < 100) && cooldown(input->data_hud, 300000))
	{
		if (input->data_hud->shieldanim.index_shield_anim == -1)
			input->data_hud->shieldanim.index_shield_anim = 0;
		input->data_hud->inventory.slot_one--;
		input->data_hud->health_bar.shield += 10;
	}
	else if (key == KEY_2 && (input->data_hud->inventory.slot_two > 0 &&
	input->data_hud->health_bar.health < 100) && cooldown(input->data_hud, 300000))
	{
		if (input->data_hud->healanim.index_heal_anim == -1)
			input->data_hud->healanim.index_heal_anim = 0;
		input->data_hud->inventory.slot_two--;
		input->data_hud->health_bar.health += 10;
	}
	else
		check_hooks3(input, key);
	
}

void check_hooks(t_input *input)
{
	int i;

	i = -1;
	while(++i < 280)
	{
		if (input->data_hud->keys[i] == 1)
		{
			if (i == KEY_R && (input->data_hud->current_ammo != 30 ||
			input->data_hud->current_ammo == 0))
			{
				if (input->data_hud->weaponanim.index_rld_anim == -1)
				input->data_hud->weaponanim.index_rld_anim = 0;
					ammo(input->data_hud);
			}
			else
				check_hooks2(input, i);
		}
	}
	input->data_hud->first_frame = 1;
}
int		redraw(void *param)
{
	t_input *input;

	input = (t_input *)param;
	clear_im(input);
	mlx_clear_window(input->data_hud->mlx_addrs, input->data_hud->win_addrs);
	if (input->data_hud->menu_state != 1)
	{
		check_hooks(input);
		check_mouse(input);
		maprotateallp(input->map, (t_fdot){.x = 0, .y = 1, .z = 0}, input);
		get_plans(input->map);
		rea_ray(input);
		proj_2d(input->map, input);
		redefinevector(input->map);
		printf("%f\n", input->angley);
	}
	if (input->angley > M_PI_2)
		input->angley = M_PI_2;
	if (input->angley < -M_PI_2)
		input->angley = -M_PI_2;
	check_anim(input->data_hud);
	print_hud(input->data_hud);
	return (0);
}
