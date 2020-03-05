/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/05 16:55:56 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 15:27:29 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# include "libft/libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/time.h>
# include "minilibx_macos/mlx.h"
# define WIN_SIZE_W 1600
# define WIN_SIZE_H 900
# define NB_HUD_TEX 15
# define NB_ANIM_TEX 4

typedef	struct		s_life
{
	int				x_min;
	int				x_max;
	int				y_min;
	int				y_max;
	int				health;
	int				shield;
}					t_life;

typedef struct		s_dot
{
	int				x;
	int				y;
}					t_dot;

typedef	struct		s_image
{
	void			*addrs;
	int				*tab;
	int				bpp;
	int				size_line;
	int				endian;
}					t_image;

typedef	struct		s_texture
{
	t_image			img;
	t_dot			pos_text;
	char			*name_text;
	int				height;
	int				width;
}					t_texture;

typedef struct		s_timer
{
	struct timeval	save_time;
	time_t			time;
	long			microsec;
}					t_timer;

typedef	struct		s_inventory
{
	int				slot_one;
	int				slot_two;
	int				slot_three;
	int				slot_four;
}					t_inventory;

typedef struct		s_keycode
{
	int				r;
	int				t;
	int				one;
	int				two;
	int				escape;
	int				l_click;
}					t_keycode;

typedef struct		s_animation
{
	t_texture		anim_texture[NB_ANIM_TEX];
	char			*tab_texture[NB_ANIM_TEX];
	int				index_heal_anim;
	int				index_shield_anim;
	int				index_wpn_anim;
	int				index_rld_anim;
}					t_animation;

typedef struct		s_data
{
	t_keycode		keycode;
	t_inventory		inventory;
	t_animation		healanim;
	t_animation		shieldanim;
	t_animation		weaponanim;
	t_texture		tab_tex[NB_HUD_TEX];
	t_texture		menu_texture[4];
	t_timer			timer;
	t_life			health_bar;
	t_dot			pos_texture[NB_HUD_TEX];
	char			*name_texture[NB_HUD_TEX];
	void			*mlx_addrs;
	void			*win_addrs;
	int				total_ammo;
	int				current_ammo;
	int				menu_state;
	int				first_frame;
}					t_data;

void				get_texture(t_data *data);
void				string_to_print(t_data *data);
void				dead_anim(t_data *data);
void				shield_animation(t_data *data);
void				reload_animation(t_data *data);
void				heal_animation(t_data *data);
void				weapon_animation(t_data *data);
void				health(t_data *data);
void				shield(t_data *data);
void				print_reload(t_data *data);
void				init_var(t_data *data);
void				fill_texture_tab(t_data *data);
void				print_ammo(t_data *data);
void				close_game(t_data *data);
int					check_inputs(t_data *data);
void				check_inputs_bis(t_data *data);
void				check_anim(t_data *data);
int					ammo(t_data *data);
int					check_fire(t_data *data);
int					print_hud(t_data *data);
int					load_texture_data(t_data *data);
int					key_press(int keycode, void *data);
int					key_release(int keycode, void *data);
int					mouse_press(int button, int x, int y, void *data);
int					mouse_release(int button, int x, int y, void *param);
int					redraw(void *data);
int					cooldown(t_data *data, time_t cd);
int					print_menu(t_data *data);
int					heal_texture_animation(t_data *data);
int					load_menu_texture(t_data *data);
int					shield_texture_animation(t_data *data);

#endif
