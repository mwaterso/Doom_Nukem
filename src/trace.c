/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   trace.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 14:48:06 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 18:04:30 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

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
	i = 0;
	poly->box.amax.x = (int)poly->projx[i].x;
	poly->box.amax.y = (int)poly->projx[i].y;
	poly->box.amin.x = (int)poly->projx[i].x;
	poly->box.amin.y = (int)poly->projx[i].y;
	//printf("p r o j x  %f %f\n", poly->projx[i].x, poly->projx[i].y);
	//printf("tobox %d %d   %d %d\n", poly->box.amin.x, poly->box.amin.y, poly->box.amax.x, poly->box.amax.y);
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


		if (data->win_h < poly->box.amax.x)
			poly->box.amax.x = data->win_h - 1;
		if (data->win_w < poly->box.amax.y)
			poly->box.amax.y = data->win_h - 1;

		if (0 > poly->box.amin.x)
			poly->box.amin.x = 0;
		if (0 > poly->box.amin.y)
			poly->box.amin.y = 0;
	}
	return (1);
}

int checkbary(t_poly *poly, t_fdot *colli)
{
	float alpha; 
	float beta;
	t_fdot BC;
	t_fdot AP;
	t_fdot AB;
	//printf("chexk bary\n");

	AB = getvect(poly->dot[0], poly->dot[1]);
	AP = getvect(poly->dot[0], *colli);
	BC = getvect(poly->dot[1], poly->dot[2]);

	//printf("colli = %lf    %lf	%lf\n", colli->x, colli->y, colli->z);
	//printf("AB = %lf    %lf	%lf\n", AB.x, AB.y, AB.z);
	//printf("BC = %lf    %lf	%lf\n", BC.x, BC.y, BC.z);
	//printf("AP = %lf    %lf	%lf\n", AP.x, AP.y, AP.z);
	//printf("%lf\n", (-AB.x * BC.y + BC.x * AB.y));
	if (checkzero(AB.z, 0.000001) && checkzero(BC.z , 0.000001))
	{
	///	printf("1 = den %lf 	num %lf\n", (BC.x * AP.y - BC.y * AB.x), (-AB.x * BC.y + BC.x * AB.y));
		alpha = (BC.x * AP.y - BC.y * AP.x) / (-AB.x * BC.y + BC.x * AB.y);
	}
	else if (checkzero(AB.y, 0.000001) && checkzero(BC.y , 0.000001))
	{
	//	printf("2 = den %lf 	num %lf\n", (BC.z * AP.x - BC.x * AB.z), (-AB.z * BC.x + BC.z * AB.x));
		alpha = (BC.z * AP.x - BC.x * AP.z) / (-AB.z * BC.x + BC.z * AB.x);
	}
	else if (checkzero(AB.x, 0.000001) || checkzero(BC.x , 0.000001))
	{
	//	printf("3 = den %lf 	num %lf\n", (BC.y * AP.z - BC.z * AB.y), (-AB.y * BC.z + BC.y * AB.z));
		alpha = (BC.y * AP.z - BC.z * AP.y) / (-AB.y * BC.z + BC.y * AB.z);
	}
	else
	{
	//	printf("4 = den %lf 	num %lf\n", (BC.x * AP.y - BC.y * AB.x), (-AB.x * BC.y + BC.x * AB.y));
		alpha = (BC.x * AP.y - BC.y * AP.x) / (-AB.x * BC.y + BC.x * AB.y);
	}
	if (BC.y != 0)
	{
	//	printf("beta = %lf  /  %lf\n", (AB.y * alpha - AP.y), BC.y);
		beta = (AB.y * alpha - AP.y) / -BC.y;
	}
	else if (BC.z != 0)
		beta = (AB.z * alpha - AP.z) / -BC.z;
	else
		beta = (AB.x * alpha - AP.x) / -BC.x;
	/*
	alp
	alpha = get3ddist(colli, poly->finaldot3d[1]) * get3ddist(colli, poly->finaldot3d[2]) / poly->areaabc;
	beta = get3ddist(colli, poly->finaldot3d[0]) * get3ddist(colli, poly->finaldot3d[2]) / poly->areaabc;*/
	//printf("----------alpha beta		%f    %f	\n", alpha, beta);

	if (alpha < 0 || beta < 0 || alpha > 1 || beta > 1 || alpha < beta)
		return (0);
	return (1);

}

int getcolli(t_ray ray, t_poly *poly, t_fdot *colli)
{
	//printf("getcolli\n");
	float t;
	double det;
	int		ret;

	//printf("%lf	%lf	%lf\n", ray.x, ray.y, ray.z);
	//printf("PLAN ||| %lf	%lf	%lf	%lf\n", poly->a, poly->b, poly->c, poly->d);
	if (!(det = (poly->a * ray.x + poly->b * ray.y + poly->c * ray.z)))
		return(0);
	//	printf("det = %lf\n", det);
	t = - poly->d / det;
	colli->x = t * ray.x;
	colli->y = t * ray.y;
	colli->z = t * ray.z;
	ret = checkbary(poly, colli);
	//printf("ret = %d\n", ret);
	if (ret)
		return (1);
	return(0);
}

int  process_ray(int x, int y, t_input *data, t_poly *poly)
{
	t_fdot colli;
//	printf("process_ray\n");
	


	if (getcolli(data->rays[y * data->win_w + x], poly, &colli))
	{
		return(1);
	}
	return(0);

}

void ray_boxes(t_input *data, t_poly *poly)
{
	t_dot p;

	poly->box.amin = (t_dot){.x = 0, .y = 0};
	poly->box.amax = (t_dot){.x = data->win_w - 1, .y = data->win_h - 1};

	p = poly->box.amin;
//	printf("rayboxes %d %d   %d %d\n", poly->box.amin.x, poly->box.amin.y, poly->box.amax.x, poly->box.amax.y);
	print_line(data, poly->box.amin, (t_dot){.x = poly->box.amax.x, .y = poly->box.amin.y}, 0xFF0000);
	print_line(data, poly->box.amin, (t_dot){.x = poly->box.amin.x, .y = poly->box.amax.y}, 0xFF0000);
	print_line(data, poly->box.amax, (t_dot){.x = poly->box.amax.x, .y = poly->box.amin.y}, 0xFF0000);
	print_line(data, poly->box.amax, (t_dot){.x = poly->box.amin.x, .y = poly->box.amax.y}, 0xFF0000);
	print_line(data, poly->box.amax, poly->box.amin, 0xFF0000);
	print_line(data, (t_dot){.x = poly->box.amax.x, .y = poly->box.amin.y}, (t_dot){.x = poly->box.amin.x, .y = poly->box.amax.y}, 0xFF0000);
	while(p.y <= poly->box.amax.y)
	{
		//printf("ray boxes\n");
		if(process_ray(p.x, p.y, data, poly))
			data->im.tab[p.x + p.y * data->win_h] = 0xFFFFFF;	

		p.x++;
		if (p.x == poly->box.amax.x)
		{
			p.y++;
			p.x = poly->box.amin.x;
		}
	}
}

