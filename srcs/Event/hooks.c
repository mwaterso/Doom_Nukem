/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hooks.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 17:39:51 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/03/03 18:57:27 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void	clear_im(t_input *data)
{
	int i;

	i = -1;
	while (++i < data->win_h * data->win_w)
	{
		data->im.tab[i] = 0;
	}
}

int checkbaryntex(t_poly *poly, t_fdot *colli)
{
	float alpha; 
	float beta;
	t_fdot BC;
	t_fdot AP;
	t_fdot AB;
	//printf("chexk bary\n");
	int i = -1;
	/*if(poly->debug)
	{

		while(++i < 3)
		printf("%d  checkbary : %lf  %lf  %lf\n", i, poly->dot[i].x, poly->dot[i].y, poly->dot[i].z);
		exit(0);
	}*/
	AB = getvect(poly->dot[0], poly->dot[1]);
	AP = getvect(poly->dot[0], *colli);
	BC = getvect(poly->dot[1], poly->dot[2]);

	//printf("colli = %lf    %lf	%lf\n", colli->x, colli->y, colli->z);
	/*if (checkzero(AB.z, 0.00001))
	{
		printf("AB = %lf    %lf	%lf\n", AB.x, AB.y, AB.z);
		printf("BC = %lf    %lf	%lf\n", BC.x, BC.y, BC.z);
	}*/
	//printf("AP = %lf    %lf	%lf\n", AP.x, AP.y, AP.z);
	//printf("%lf\n", (-AB.x * BC.y + BC.x * AB.y));
	if ((checkzero(AB.x, 0.0001) && checkzero(BC.x , 0.0001)) || (checkzero(AB.y, 0.0001) && checkzero(AB.x , 0.0001)))
	{
		//printf("3 = den %lf 	num %lf\n", (BC.y * AP.z - BC.z * AB.y), (-AB.y * BC.z + BC.y * AB.z));
		alpha = (BC.y * AP.z - BC.z * AP.y) / (-AB.y * BC.z + BC.y * AB.z);
	}
	else if (checkzero(AB.z, 0.0001) && checkzero(BC.z , 0.0001))
	{
	///	printf("1 = den %lf 	num %lf\n", (BC.x * AP.y - BC.y * AB.x), (-AB.x * BC.y + BC.x * AB.y));
		alpha = (BC.x * AP.y - BC.y * AP.x) / (-AB.x * BC.y + BC.x * AB.y);
	}
	else if (checkzero(AB.y, 0.0001) && checkzero(BC.y , 0.0001))
	{
	//	printf("2 = den %lf 	num %lf\n", (BC.z * AP.x - BC.x * AB.z), (-AB.z * BC.x + BC.z * AB.x));
		alpha = (BC.z * AP.x - BC.x * AP.z) / (-AB.z * BC.x + BC.z * AB.x);
	}
	else if (!checkzero(-AB.x * BC.y + BC.x * AB.y, 0.0001))
	{
		//printf("4 = den %lf 	num %lf\n", (BC.x * AP.y - BC.y * AB.x), (-AB.x * BC.y + BC.x * AB.y));
		alpha = (BC.x * AP.y - BC.y * AP.x) / (-AB.x * BC.y + BC.x * AB.y);
	}
	else
	{
	//	printf("2 = den %lf 	num %lf\n", (BC.z * AP.x - BC.x * AB.z), (-AB.z * BC.x + BC.z * AB.x));
		alpha = (BC.z * AP.x - BC.x * AP.z) / (-AB.z * BC.x + BC.z * AB.x);
	}
	if (!checkzero(BC.y, 0.0001))
	{
	//	printf("beta = %lf  /  %lf\n", (AB.y * alpha - AP.y), BC.y);
		beta = (AB.y * alpha - AP.y) / -BC.y;
	}
	else if (!checkzero(BC.z, 0.0001))
		beta = (AB.z * alpha - AP.z) / -BC.z;
	// else if (!checkzero(BC.x, 0.000001))
	// 	beta = (AB.z * alpha - AP.z) / -BC.x;
	else
		beta = (AB.x * alpha - AP.x) / -BC.x;
	/*
	alp
	alpha = get3ddist(colli, poly->finaldot3d[1]) * get3ddist(colli, poly->finaldot3d[2]) / poly->areaabc;
	beta = get3ddist(colli, poly->finaldot3d[0]) * get3ddist(colli, poly->finaldot3d[2]) / poly->areaabc;*/
	//printf("----------alpha beta		%f    %f	\n", alpha, beta);

	if (alpha < 0 || beta < 0 || alpha > 1 || beta > 1 || alpha < beta)
		return (0);
	//return (gettex(beta, alpha, poly));
	/*if (alpha != alpha)
	{
		printf("AB = %lf    %lf	%lf\n", AB.x, AB.y, AB.z);
		printf("BC = %lf    %lf	%lf\n", BC.x, BC.y, BC.z);
		printf("alpha = %f\n", alpha);
	}*/
	return (1);

}

int	get_ortho(t_poly *poly, t_fdot *colli, t_ray *ray)
{

	float t;
	double det;
	int		ret;
	float dist;

	ret = -1;

	//printf("getcolli\n");
	//printf("%lf	%lf	%lf\n", ray.x, ray.y, ray.z);
	//printf("PLAN ||| %lf	%lf	%lf	%lf\n", poly->a, poly->b, poly->c, poly->d);
	if (!(det = (poly->a * ray->x + poly->b * ray->y + poly->c * ray->z)))
		return(0);
	//	printf("det = %lf\n", det);
	t = - poly->d / det;
	colli->x = t * ray->x;
	colli->y = t * ray->y;
	colli->z = t * ray->z;

	return(1);


	//if
	/*t_fdot	point;
	float	t;

	if (poly->a != 0)
		t = poly->dot[0].x / poly->a - 1;
	else if (poly->b != 0)
		t = poly->dot[0].y / poly->b - 1;
	else if (poly->c != 0)
		t = poly->dot[0].z / poly->c - 1;
	
	printf("plan = %f		%f		%f\n", poly->a, poly->b, poly->c);
	printf("point = %f		%f		%f\n", poly->dot[0].x, poly->dot[0].y, poly->dot[0].z);
	point.x = t * poly->a + poly->dot[0].x;
	point.y = t * poly->b + poly->dot[0].y;
	point.z = t * poly->c + poly->dot[0].z;

	return(point);*/
}

void rea_ray(t_input *data)
{
	int i;

	i = -1;
	while(++i < data->win_h * data->win_w)
	{
		data->rays[i].distcolli = -1;
	}

}

int checkseg(t_poly *poly)
{
	float pa;
	float pb;
	float pc;
	if((pa = get3ddist((t_fdot){.x = 0, .y = 0, .z = 0}, poly->dot[0])) < HITBOXRAY)
		return(1);
	if((pb = get3ddist((t_fdot){.x = 0, .y = 0, .z = 0}, poly->dot[1])) < HITBOXRAY)
		return(1);
	if((pc = get3ddist((t_fdot){.x = 0, .y = 0, .z = 0}, poly->dot[2])) < HITBOXRAY)
		return(1);
	return(0);
}

int check_colli(t_poly *poly)
{
	t_fdot ortho;

	while(poly)
	{
		if((get_ortho(poly, &ortho, &(t_ray){.x = poly->a, .y = poly->b, .z = poly->b})))
		{	
			if(get3ddist((t_fdot){.x = 0, .y = 0, .z = 0}, ortho) < HITBOXRAY)
			{
				//printf("%f\n", ortho);
				if(checkbaryntex(poly, &ortho))
					return(1);
				else if(checkseg(poly))
					return(1);
			}
		}
		printf("%f		%f		%f\n", ortho.x, ortho.y, ortho.z);
		poly = poly->next;
	}
	return(0);
}

/*

				FONCTION COLLISION


proj orto O du perso sur le plan -> distance O-joueur 

si OJ < r

plusieurs collision 

si OJ == r

une seule collision



collision

si coo

*/

int	keyboard_move(int key, t_input *inputs)
{
	//printf("key  %d\n", key);
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_RIGHT || key == KEY_LEFT)
		moove(inputs, key);
	if (key == KEY_J)
		inputs->debug = (inputs->debug ? 0 : 1);
	if (key == KEY_W)
		inputs->angley += ROTY;
	if (key == KEY_S)
		inputs->angley -= ROTY;
	if (inputs->angley > M_PI_2)
		inputs->angley = M_PI_2;
	if (inputs->angley < -M_PI_2)
		inputs->angley = -M_PI_2;
	if (key == KEY_A)
		maprotateallp(inputs->map, (t_fdot){.x = 0, .y = 0, .z = -1}, inputs);
	if (key == KEY_D)
		maprotateallp(inputs->map, (t_fdot){.x = 0, .y = 0, .z = 1}, inputs);
	//printf("--------------------------------------------------------------------------%lf\n", inputs->angley);
	maprotateallp(inputs->map, (t_fdot){.x = 0, .y = 1, .z = 0}, inputs);
	get_plans(inputs->map);
	mlx_clear_window(inputs->mlx_ad, inputs->win_ad);
	clear_im(inputs);
	rea_ray(inputs);
	proj_2d(inputs->map, inputs);
	if (key == KEY_G)
		mlx_put_image_to_window(inputs->mlx_ad, inputs->win_ad, inputs->map->texture.ad, 0, 0);
	int i = -1;
//	while(++i < 3)
//		printf("%d ouais : %lf  %lf  %lf\n", i, inputs->map->dot[i].x, inputs->map->dot[i].y, inputs->map->dot[i].z);
	i = -1;
	/*while(++i < 3)
		printf("%d ouais : %lf  %lf  %lf\n", i, inputs->map->next->dot[i].x, inputs->map->next->dot[i].y, inputs->map->next->dot[i].z);*/
	return(1);
}