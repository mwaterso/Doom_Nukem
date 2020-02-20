/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:53:16 by beduroul          #+#    #+#             */
/*   Updated: 2020/02/20 10:53:18 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
# define PARSING_H

# include "doom.h"

enum {NUM, TEX, CORD, BRACKET, O_BRACKET, TEX_E, TEX_X, BLOCK, D_OBJ};

typedef struct		s_2d
{
   float			x;
   float			y;
}					t_2d;


typedef struct		s_index
{
	int				i;
	int				j;
	int           	k;
}					t_index;

typedef struct		s_tex
{
	int		*tab;
	int		width;
	int		height;
}					t_tex;

typedef struct		s_color
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
}					t_color;

typedef	struct		s_mtl
{
	t_tex			tex;
	t_color			ka;
	t_color			kd;
}					t_mtl;

typedef	struct		s_lst_mtl
{
	char				*name;
	t_mtl				mtl;
	struct s_lst_mtl	*next;
}					t_lst_mtl;

typedef struct s_poly
{
	t_2dbox			box;
  	t_fdot			dot[NBR_PPOLY];
	t_fdot			dot_vn[NBR_PPOLY];
	t_fdot			rotx[NBR_PPOLY];
	t_fdot			projx[NBR_PPOLY];
   	t_2d			cord[NBR_PPOLY];
	t_fdot			normale;
	float			a;
	float			b;
	float			c;
	float			d;
	char			*tex;
	float			areaabc;
	int				nbr_p;
	int				nbr_pprojx;
	t_tex			tex_tab;
	t_mtl			mtl;
	struct s_poly 	*next;

}					t_poly;

typedef struct			s_object
{
	t_fdot				pos;
	t_fdot				rot;
	t_poly				*poly;
	char				*file;
	char				*l_file;
	struct s_object		*next;
}						t_object;

typedef struct 		s_lstex
{
	t_tex			tex;
	char			*name;
	struct s_lstex	*next;
}					t_lstex;

typedef struct		s_file_obj
{
	t_lst_mtl		*lst;
	t_fdot      	*v;
    t_2d        	*vt;
    t_fdot      	*vn;
}					t_file_obj;

#endif