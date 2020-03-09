/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Projection.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/17 19:34:19 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/03/09 18:07:58 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

t_fdot getnew_point(t_fdot frst_point, t_fdot scd_point)
{
	t_fdot a;
	//printf("						new point\n");
	//printf("1=				%lf	%lf	%lf\n", a.x, a.y, a.z);
	//a.y = frst_point.x - (scd_point.y - frst_point.y)/(scd_point.x - frst_point.x);
	a.y = (scd_point.y - frst_point.y) * ((1 - frst_point.x) / (scd_point.x - frst_point.x)) + frst_point.y;
	a.z = (scd_point.z - frst_point.z) * ((1 - frst_point.x) / (scd_point.x - frst_point.x)) + frst_point.z;
	a.x = 1;
	//printf("						new point		%lf	%lf	%lf\n", a.x, a.y, a.z);
	return (a);
}

void separate_points(t_poly *map) /* 		 ===>		Ax < 0		<===      */
{
	int j;
	int k;
	int o;

	int i = -1;
	t_fdot tmp;

	//while(++i < 3)
	// 	printf("points: %lf  %lf  %lf\n", map->dot[i].x, map->dot[i].y, map->dot[i].z);
	o = 0;
	k = 0;
	j = -1;
	map->nbr_pprojx = 0;
	while (++j < 3)
	{
		 if (j == 2)
		 	k = 0;
		 else
			k = j + 1;
	 	//printf("%d				points: %lf  %lf  %lf\n", j, map->dot[j].x, map->dot[j].y, map->dot[j].z);
	 	//printf("%d				points2: %lf  %lf  %lf\n", k,  map->dot[k].x, map->dot[k].y, map->dot[k].z);
		if (map->dot[j].x > 0 && map->dot[k].x > 0)
		{
			//printf("1w r : %d x = %f y = %f z = %f\n", j, map->dot[j].x, map->dot[j].y, map->dot[j].z);
			map->projx[o++] = map->dot[j];
		//	printf("1w r : %d x = %f y = %f z = %f\n", j, map->projx[j].x, map->projx[j].y, map->projx[j].z);
		}
		else if (map->dot[j].x > 0 && map->dot[k].x <= 0)
		{
			//printf("2w r : %d x = %f y = %f z = %f\n", j, map->dot[j].x, map->dot[j].y, map->dot[j].z);
			map->projx[o++] = map->dot[j];
			tmp = getnew_point(map->dot[j], map->dot[k]);
			map->projx[o++] = tmp;
		//	printf("2w r : %d x = %f y = %f z = %f\n", j, tmp.x, tmp.y, tmp.z);
		}
		else if (map->dot[j].x <= 0 && map->dot[k].x > 0)
		{
			// printf("3w r : %d x = %f y = %f z = %f\n", j, map->dot[j].x, map->dot[j].y, map->dot[j].z);
			//map->projx[o++] = getnew_point(map->dot[j], map->dot[k]);
			tmp = getnew_point(map->dot[k], map->dot[j]);
			map->projx[o++] = tmp;
			// printf("						new point		%lf	%lf	%lf\n", map->projx[j].x, map->projx[j].y, map->projx[j].z);
			//if(k == NBR_PPOLY - 1)
			//	map->nbr_pprojx = NBR_PPOLY;
		//	printf("3w r : %d x = %f y = %f z = %f\n", j, tmp.x, tmp.y, tmp.z);
		//	printf("3w r : %d x = %f y = %f z = %f\n", j, map->projx[j].x, map->projx[j].y, map->projx[j].z);
		}
		/*else if(map->dot[j].x <= 0 && map->dot[k].x <= 0)
		{
			if(j == 0)
				o = map->nbr_pprojx - 1;
			else
				o = j - 1;
			if (map->dot[o].x > 0)
			{
				// printf("4w r : %d x = %f y = %f z = %f\n", j, map->dot[j].x, map->dot[j].y, map->dot[j].z);
				map->projx[o] = getnew_point(map->dot[j], map->dot[o]);
				// printf("4w r : %d x = %f y = %f z = %f\n", j, map->projx[j].x, map->projx[j].y, map->projx[j].z);
			}*/
	}
		//printf("-----------------   %d   ----------------\n", j);
		//printf("map->nbr_pprojx  = %d\n", map->nbr_pprojx);
	//}
	//if (map->nbr_pprojx != NBR_PPOLY)
	//	map->nbr_pprojx = map->nbr_p;
	map->nbr_pprojx = o;
	//printf("%d\n", o);
	// int i = -1;
	// while (++i < 4)
		// printf("Dot : %d x = %f y = %f z = %f\n", i, map->dot[i].x, map->dot[i].y, map->dot[i].z);
	// i = -1;
	// while (++i < 4)
		// printf("Sep points  |||   Dot : %d x = %f y = %f z = %f\n", i, map->projx[i].x, map->projx[i].y, map->projx[i].z);
} 


int 	Projxy(t_poly *map, t_input *data)
{
	double fov_x = X_VIEW;
	double fov_z = Z_VIEW;
	double tmp;

	int j = -1;
	int i = -1;
	//while(++i < map->nbr_pprojx)
//	 	printf("%d  projection : %lf  %lf  %lf\n", i, map->projx[i].x, map->projx[i].y, map->projx[i].z);
	while (++j < map->nbr_pprojx)
	{
		//printf("	%d----	PROXY		%lf	%lf	%lf\n", map->nbr_pprojx, map->projx[j].x, map->projx[j].y, map->projx[j].z);
		//printf("x = %lf / %lf - %lf * %d / %lf\n", map->projx[j].z, map->projx[j].x, fov_z / 2, (data->win_h - 1), fov_z);
		// printf("frg %d, %f, %lf\n", data->win_h, fov_z, (double)data->win_h / fov_z);
		//printf("alpha : %f\n", ((map->projx[j].z / map->projx[j].x) - fov_z / 2) * ((double)(data->win_h - 1) / fov_z));
		tmp = map->projx[j].x;
		map->projx[j].x = ((map->projx[j].y / map->projx[j].x) + fov_x / 2) * ((double)(data->win_w - 1) / fov_x);
		map->projx[j].y = (-(map->projx[j].z / tmp) + fov_z / 2) * ((double)(data->win_h - 1) / fov_z);
		//printf("point %d x = %lf y = %lf\n", j, map->projx[j].x, map->projx[j].y);
	}
	if(map->nbr_pprojx)
		return(1);
	return(0);
}

int proj_2d(t_poly *map, t_input *data)
{
	int i;
	int ret;
	
	i = -1;
    while (map)
	{
		i++;
		//while(++i < 3)
		//	printf("%d  projection : %lf  %lf  %lf\n", i, map->dot[i].x, map->dot[i].y, map->dot[i].z);
		separate_points(map);
		ret = Projxy(map, data);
		if (ret)
		{
			map->isvisible = 1;
			poly_toboxes(data, map);
			ray_boxes(data, map);
		}
		else
		{
			map->isvisible = 0;
			printf("non print : %d\n", i);
		}
		
		map = map->next;
	}
	//printf("%p		%p\n", data->im.tab, data->im.ad);
	mlx_put_image_to_window(data->mlx_ad, data->win_ad, data->im.ad, 0, 0);
	return(1);
}