/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/15 15:38:23 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 18:19:05 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "../libft/include/libft.h"
# include "../minilibx_macos/mlx.h"
# include <stdio.h>
# include <math.h>
# include "keyboard.h"
# include <pthread.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <openAL/AL.h>
# include <openAL/alc.h>
# define NB_THREAD		8
# define NB_TEXTURE		4
# define X_VIEW			M_PI / 2
# define Z_VIEW			M_PI / 2
//# define X_VIEW			3.1415926535
//# define Z_VIEW			3.1415926535
# define m_3PI_2		4.71238898038
# define m_PI3			1.0471975512
# define ROTX			0.05
# define ROTZ			0.05
# define ROTY			0.05
# define NBR_PPOLY		4
# define NBR_PIX		1000000
# define GROUNDCOLOR	0x000000



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

typedef struct		s_ray
{
	double				x;
	double				y;
	double				z;
	double				bx;
	double				by;
	double				bz;

	double				dist;
}					t_ray;

typedef struct		s_fdot
{
	double			x;
	double			y;
	double			z;
}					t_fdot;

typedef struct		s_dot
{
	int				x;
	int				y;
	int				z;
}					t_dot;


typedef struct		s_line
{
   char				*line;
   int				n_line;
   struct s_line	*next;
}					t_line;

typedef struct		s_3x3matrix
{
	float a1;
	float a2;
	float a3;

	float b1;
	float b2;
	float b3;

	float c1;
	float c2;
	float c3;
}					t_3x3matrix;

typedef struct		s_fov
{
	double				rotx;
	double				roty;
	struct s_fov 		*next;
}					t_fov;

typedef struct	s_2dbox
{
	t_dot amin;
	t_dot amax;
}				t_2dbox;

typedef struct		s_image
{
	void			*ad; 				//img
	int				*tab;				//addr
	int				bits_per_pixel;		//bpp
	int				size_line;   		//s_l
	int				endian;
}					t_image;

typedef	struct		s_texture
{
	int				height;
	int				width;
	t_image			im;
}					t_texture;

typedef struct		s_thread
{
	pthread_t		thread;
	int				i_start;
	int				i_end;
	int				index;
	t_fov			*fov;
	struct s_input	*inputs;
}					t_thread;

typedef struct		s_tex
{
	void			*tab;
	unsigned int	*img;
	int				width;
	int				height;
	int				bpp;
	int				s_l;
	int				endian;
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

typedef struct		s_input
{   
	void			*mlx_ad;
	void			*win_ad;
	t_image			im;
	void 			**tab_win;
	t_thread		thread_tab[NB_THREAD];
    int				win_h;
    int				win_w;
	double			alpha_x;   /* angle entre vue joueur et vect x sur plan xy (PROJECTION 2D)*/
	double			alpha_z;   /* angle entre vue joueur et vect z */
	int				nbrpoly;
	t_poly			*map;
	t_object		*obj;
	t_fdot			dir;
	t_fov			*fov;
	t_ray			*rays;
	t_3x3matrix		rotz;
	t_3x3matrix		roty;

}					t_input;

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
	t_index			size;
}					t_file_obj;


/*typedef struct		s_octree
{
	struct s_octree (*childs)[8];
	int color;
	double size;
	t_fdot end_corner;		/Coordonnees du sommet +z +x +y/
	t_fdot start_corner;	/Coordonnees du sommet -z -x -y/
}					t_octree;*/


double 			get3ddist(t_fdot a, t_fdot b);
void			get_plans(t_poly *poly);
void			ray_boxes(t_input *data, t_poly *poly);
void 			mapmoveallp(t_poly *poly, t_fdot incr);
void 			maprotateallp(t_poly *poly, t_fdot rot, t_input *data);
void		   	free_poly(t_poly **poly);
void		   	free_poly(t_poly **poly);
void		   	free_line(t_line **line);
void		   	error_file(int fd, char *av);
void		  	poly_error(t_line *list, int error, int i, int *err);
void			print_s(int i);
void    		get_device(char **device);
void 			print_parse(t_poly *poly);
int				check_error(t_line *list);
int				poly_toboxes (t_input *data, t_poly *poly);
int				proj_2d(t_poly *map, t_input *data);
int				keyboard_move(int key, t_input *inputs);
int				push_back(t_poly *new, t_poly **poly);
int				creat_elem_l(char *line, int n_line, t_line **list);
int		   		sort_dot(char *line, t_poly *new, t_index *index);
t_fdot			ApplyMatPoint(t_3x3matrix matrix, t_fdot point);
t_fdot 			getvect(t_fdot a, t_fdot b);
t_poly			*parsing_poly(char *file, t_input *data);
int				parse_loop(t_poly **poly, t_line *list, t_input *data, int fd);
int				parse_file(t_line *list, t_poly **poly, t_input *data);
int				load_tex(t_poly **poly, t_input *data);
char			*sort_file(char *line);


t_line			*read_obj(t_line *list, t_object **obj, t_input *data);
void			push_front_obj(t_object *new, t_object **obj);
void             reverse(t_object **obj);
void             poly_rev(t_poly **poly) ;
void 			obj_error(t_line *list, int *error);
t_poly			*ft_pares_obj(char *file, t_input *data);
int      		sort_tfdot(char *line, t_fdot *dot);
int      		sort_t2d(char *line, t_2d *dot);
int         	sort_poly(char *line, t_poly **poly, t_file_obj file, char *mtl);
void			free_tab(char ***tab);
/*------------------------------*/
void 			print_parse1(t_poly *poly);
/*-------------------------------*/
void			push_front_pol(t_poly *new, t_poly **poly);
void             reverse_p(t_poly **poly);
void             reverse_o(t_object **obj);
void             reverse_l(t_line **list);
void    sort_mtl(t_input *data, char *file, t_file_obj *f);
int		creat_elem_l1(char *line, int n_line, t_line **list);
int      sort_color(char *line, t_color *color);
char    *sort_material(char *line);
void			push_front_mtl(t_lst_mtl *new, t_lst_mtl **mtl);
void            free_file(t_lst_mtl **lst);

#endif

