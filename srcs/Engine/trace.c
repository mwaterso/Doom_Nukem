/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   trace.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 14:48:06 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/03/09 18:00:00 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int checkzero(float a, float inter)
{
	//printf("??%f		%d\n", a, (a < (0 + inter) && a > (0 - inter)) ? 1 : 0);
	return((a < (0 + inter) && a > (0 - inter)) ? 1 : 0);
}

int		tallnomin(int a, int b)
{
	int	e;
	int	r;

	e = a;
	r = b;
	if (a < 0)
		a *= -1;
	if (b < 0)
		b *= -1;
	if (a >= b)
		return (a);
	return (b);
}

void	print_line(t_input *input, t_dot a, t_dot b, int color)
{
	double	dx;
	double	dy;
	int		tall;
	int		i;

	i = 0;
	if (b.x == a.x && b.y == a.y)
		return ;
	tall = tallnomin(a.y - b.y, a.x - b.x);
	dx = (double)(a.x - b.x) / tall;
	dy = (double)(a.y - b.y) / tall;
	while (i++ < tall)
	{
		if ((i * dx + b.x) >= 0 && (i * dx + b.x) < input->win_w &&
		(i * dy + b.y) < input->win_h && (i * dy + b.y) >= 0)
			input->im.tab[((int)(i * dx + b.x) +
			(int)(i * dy + b.y) * (input->im.size_line / 4))] = color;
	}
}

int poly_toboxes (t_input *data, t_poly *poly)
{
	int i;
	i = -1;
	poly->box.amax.x = (int)poly->projx[0].x;
	poly->box.amax.y = (int)poly->projx[0].y;
	poly->box.amin.x = (int)poly->projx[0].x;
	poly->box.amin.y = (int)poly->projx[0].y;
	
	//printf("NBR POINTS %d			%d	%d\n%d	%d\n", poly->nbr_pprojx, poly->box.amin.x, poly->box.amin.y, poly->box.amax.x, poly->box.amax.y);
	//while(++i < poly->nbr_pprojx)
	// 	printf("%d  projection : %lf  %lf  %lf\n", i, poly->projx[i].x, poly->projx[i].y, poly->projx[i].z);
	i = -1;
	while (++i < poly->nbr_pprojx)
	{
		if (poly->projx[i].x > poly->box.amax.x)
			poly->box.amax.x = poly->projx[i].x;
		if (poly->projx[i].y > poly->box.amax.y)
			poly->box.amax.y = poly->projx[i].y;

		if (poly->projx[i].x < poly->box.amin.x)
			poly->box.amin.x = poly->projx[i].x;
		if (poly->projx[i].y < poly->box.amin.y)
			poly->box.amin.y = poly->projx[i].y;


	}
		if (data->win_w <= poly->box.amax.x)
			poly->box.amax.x = data->win_w - 1;
		if (data->win_h <= poly->box.amax.y)
			poly->box.amax.y = data->win_h - 1;
		if (data->win_w <= poly->box.amin.x)
			poly->box.amin.x = data->win_w - 1;
		if (data->win_h <= poly->box.amin.y)
			poly->box.amin.y = data->win_h - 1;
		if (0 > poly->box.amin.x)
			poly->box.amin.x = 0;
		if (0 > poly->box.amin.y)
			poly->box.amin.y = 0;
		if (0 > poly->box.amax.x)
			poly->box.amax.x = 0;
		if (0 > poly->box.amax.y)
			poly->box.amax.y = 0;
	//	printf("min-%d	%d\nmax-%d	%d\n", poly->box.amin.x, poly->box.amin.y, poly->box.amax.x, poly->box.amax.y);
	return (1);
}

int gettex(float ab, float bc, t_poly *poly)
{	
	int ret;
	int max;
	max = poly->tex_tab.width * poly->tex_tab.height - 1;
	//printf("1\n");
	//printf("2\n");
	ret = (int)(((double)(ab * poly->ab.x) + (double)(bc * poly->bc.x) + poly->a2d.x) + (int)((double)(ab * poly->ab.y) + (double)(bc * poly->bc.y) + poly->a2d.y) * (poly->tex_tab.width));
	if (ret > max)
		ret = max;
	else if (ret < 0)
	{
		//printf("ret = %d  y = %d	x = %f\n", ret, (int)((double)(ab * poly->ab.y) + (double)(bc * poly->bc.y) + poly->a2d.y), (ab * poly->ab.x) + (double)(bc * poly->bc.x) + poly->a2d.x);
		//printf("ab = %f		bc = %f		ab.x = %f ab.y = %f  bc.x = %f bc.y = %f   a.x = %f a.y = %f\n", ab, bc, poly->ab.x, poly->ab.y, poly->bc.x, poly->bc.y, poly->a2d.x, poly->a2d.y);
		ret = 0;
	}
	//printf("%d\n", poly->tex_tab.img[ret]);
	return(poly->tex_tab.img[ret]);
}


int checkbary(t_poly *poly, t_fdot *colli, int frst)
{
	float alpha; 
	float beta;
	t_fdot	AP;
	//printf("chexk bary\n");
	int i = -1;
	/*if(poly->debug)
	{

		while(++i < 3)
		printf("%d  checkbary : %lf  %lf  %lf\n", i, poly->dot[i].x, poly->dot[i].y, poly->dot[i].z);
		exit(0);
	}*/
	//if(frst)
	//{
	//	poly->vAB = getvect(poly->dot[0], poly->dot[1]);
	//	poly->vBC = getvect(poly->dot[1], poly->dot[2]);
	//}

	AP = getvect(poly->dot[0], *colli);
	//printf("colli = %lf    %lf	%lf\n", colli->x, colli->y, colli->z);
	/*if (checkzero(AB.z, 0.00001))
	{
		printf("AB = %lf    %lf	%lf\n", AB.x, AB.y, AB.z);
		printf("BC = %lf    %lf	%lf\n", BC.x, BC.y, BC.z);
	}*/
	//printf("AP = %lf    %lf	%lf\n", poly->vAP.x, poly->vAP.y, poly->vAP.z);
	//printf("%lf\n", (-AB.x * BC.y + BC.x * AB.y));
	if ((checkzero(poly->vAB.x, 0.0001) && checkzero(poly->vBC.x , 0.0001)) || (checkzero(poly->vAB.y, 0.0001) && checkzero(poly->vAB.x , 0.0001)))
	{
		//printf("3 = den %lf 	num %lf\n", (poly->vBC.y * AP.z - poly->vBC.z * AB.y), (-AB.y * poly->vBC.z + poly->vBC.y * AB.z));
		alpha = (poly->vBC.y * AP.z - poly->vBC.z * AP.y) / poly->den1;
	}
	else if (checkzero(poly->vAB.z, 0.0001) && checkzero(poly->vBC.z , 0.0001))
	{
	///	printf("1 = den %lf 	num %lf\n", (poly->vBC.x * AP.y - poly->vBC.y * AB.x), (-AB.x * poly->vBC.y + poly->vBC.x * AB.y));
		alpha = (poly->vBC.x * AP.y - poly->vBC.y * AP.x) / poly->den2
		;
	}
	else if (checkzero(poly->vAB.y, 0.0001) && checkzero(poly->vBC.y , 0.0001))
	{
	//	printf("2 = den %lf 	num %lf\n", (poly->vBC.z * AP.x - poly->vBC.x * AB.z), (-AB.z * poly->vBC.x + poly->vBC.z * AB.x));
		alpha = (poly->vBC.z * AP.x - poly->vBC.x * AP.z) / poly->den3;
	}
	else if (!checkzero(-poly->vAB.x * poly->vBC.y + poly->vBC.x * poly->vAB.y, 0.0001))
	{
		//printf("4 = den %lf 	num %lf\n", (poly->vBC.x * AP.y - poly->vBC.y * AB.x), (-AB.x * poly->vBC.y + poly->vBC.x * AB.y));
		alpha = (poly->vBC.x * AP.y - poly->vBC.y * AP.x) / poly->den2;
	}
	else
	{
	//	printf("2 = den %lf 	num %lf\n", (poly->vBC.z * AP.x - poly->vBC.x * AB.z), (-AB.z * poly->vBC.x + poly->vBC.z * AB.x));
		alpha = (poly->vBC.z * AP.x - poly->vBC.x * AP.z) / poly->den3;
	}
	if (!checkzero(poly->vBC.y, 0.0001))
	{
	//	printf("beta = %lf  /  %lf\n", (AB.y * alpha - AP.y), poly->vBC.y);
		beta = (poly->vAB.y * alpha - AP.y) / -poly->vBC.y;
	}
	else if (!checkzero(poly->vBC.z, 0.0001))
		beta = (poly->vAB.z * alpha - AP.z) / -poly->vBC.z;
	// else if (!checkzero(poly->vBC.x, 0.000001))
	// 	beta = (AB.z * alpha - AP.z) / -poly->vBC.x;
	else
		beta = (poly->vAB.x * alpha - AP.x) / -poly->vBC.x;
	/*
	alp
	alpha = get3ddist(colli, poly->finaldot3d[1]) * get3ddist(colli, poly->finaldot3d[2]) / poly->areaabc;
	beta = get3ddist(colli, poly->finaldot3d[0]) * get3ddist(colli, poly->finaldot3d[2]) / poly->areaabc;*/
	//printf("----------alpha beta		%f    %f	\n", alpha, beta);

	if (alpha < 0 || beta < 0 || alpha > 1 || beta > 1 || alpha < beta)
		return (-1);
	//return (gettex(beta, alpha, poly));
	/*if (alpha != alpha)
	{
		printf("AB = %lf    %lf	%lf\n", AB.x, AB.y, AB.z);
		printf("BC = %lf    %lf	%lf\n", BC.x, BC.y, BC.z);
		printf("alpha = %f\n", alpha);
	}*/
	//return (0xff0000);
	return (gettex(alpha, beta, poly));

}

int getcolli(t_ray *ray, t_poly *poly, t_fdot *colli, int frst)
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
		return(-1);
	//	printf("det = %lf\n", det);
	t = - poly->d / det;
	colli->x = t * ray->x;
	colli->y = t * ray->y;
	colli->z = t * ray->z;
	//if (poly->debug == 2)
//	{
//		printf("==================%lf	%lf	%lf	 %f====================\n", ray.x, ray.y, ray.z, poly->d);
//		printf("==================%lf	%lf	%lf====================\n", colli->x, colli->y, colli->z);
//	}
	//printf("getcolli\n");
	if (ray->distcolli == -1)
		ret = 2;
	else if ((dist = get3ddist((t_fdot){.x = 0, .y = 0, .z = 0}, *colli) < ray->distcolli))
		ret = 1;

	if (ret == 1)
	{
		if ((ret = checkbary(poly, colli, frst)) == -1)
			ret = -1;
		else
			ray->distcolli = dist;
	}
	else if (ret == 2)
	{
		if ((ret = checkbary(poly, colli, frst)) == -1)
		{
			ray->distcolli = -1;
			ret = -1;
		}
		else
			ray->distcolli = get3ddist((t_fdot){.x = 0, .y = 0, .z = 0}, *colli);
	}
	
	//printf("ret = %d\n", ret);
	return (ret);
}

int  process_ray(t_proray ray, t_input *data, t_poly *poly)
{
	t_fdot	colli;
	//printf("process_ray\n");
	

	if (ray.y * data->win_w + ray.x == 500)
			poly->debug = 2;
	else
			poly->debug = 0;
	/*if (getcolli(data->rays[y * data->win_w + x], poly, &colli, &texcol))
	{
		return(1);
	}*/

	//printf("procerrrrrrerrrrrrrrrrrrrrrrrrn													%d\n", ray.frst);
	return(getcolli(&(data->rays[ray.y * data->win_w + ray.x]), poly, &colli, ray.frst));

}

void ray_boxes(t_input *data, t_poly *poly)
{
	t_dot p;
	int ret;

	//poly->box.amin = (t_dot){.x = 0, .y = 0};
	//poly->box.amax = (t_dot){.x = data->win_w - 1, .y = data->win_h - 1};

	p = poly->box.amin;
	//printf("rayboxes %d %d   %d %d\n", p.x, p.y, poly->box.amax.x, poly->box.amax.y);
	//print_line(data, poly->box.amin, (t_dot){.x = poly->box.amax.x, .y = poly->box.amin.y}, 0xFF0000);
	//print_line(data, poly->box.amin, (t_dot){.x = poly->box.amin.x, .y = poly->box.amax.y}, 0xFF0000);
	//print_line(data, poly->box.amax, (t_dot){.x = poly->box.amax.x, .y = poly->box.amin.y}, 0xFF0000);
	//print_line(data, poly->box.amax, (t_dot){.x = poly->box.amin.x, .y = poly->box.amax.y}, 0xFF0000);
	//print_line(data, poly->box.amax, poly->box.amin, 0xFF0000);
	//print_line(data, (t_dot){.x = poly->box.amax.x, .y = poly->box.amin.y}, (t_dot){.x = poly->box.amin.x, .y = poly->box.amax.y}, 0xFF0000);
	if (!(poly->box.amin.x == poly->box.amax.x || poly->box.amin.y == poly->box.amax.y))
	{
		while(p.y <= poly->box.amax.y)
		{
			if (data->debug)
			{
				printf("ray boxes : %d %d\n", p.x, p.y);
				printf("min-%d	%d\nmax-%d	%d\n", poly->box.amin.x, poly->box.amin.y, poly->box.amax.x, poly->box.amax.y);
			}
			if(p.x == poly->box.amin.x && p.y == poly->box.amin.y)
				ret = process_ray((t_proray){.x = p.x, .y = p.y, 0}, data, poly);
			else
				ret = process_ray((t_proray){.x = p.x, .y = p.y, 0}, data, poly);
			if (ret != -1)
				data->im.tab[p.x + p.y * data->win_w] = ret; 
			p.x++;
			if (p.x == poly->box.amax.x)
			{
				p.y++;
				p.x = poly->box.amin.x;
			}
		}
	}	
}

