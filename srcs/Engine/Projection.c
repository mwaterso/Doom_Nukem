/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Projection.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/17 19:34:19 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 18:45:14 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

t_fdot getnew_point(t_fdot frst_point, t_fdot scd_point)
{
	t_fdot a;
	printf("						new point\n");
	printf("1=				%lf	%lf	%lf\n", a.x, a.y, a.z);
	//a.y = frst_point.x - (scd_point.y - frst_point.y)/(scd_point.x - frst_point.x);
	a.y = (scd_point.y - frst_point.y) * ((1 - frst_point.x) / (frst_point.x - scd_point.x)) + frst_point.y;
	a.z = (scd_point.z - frst_point.z) * ((1 - frst_point.x) / (frst_point.x - scd_point.x)) + frst_point.z;
	a.x = 1;
	printf("						new point		%lf	%lf	%lf\n", a.x, a.y, a.z);
	return (a);
}

void separate_points(t_poly *map) /* 		 ===>		Ax < 0		<===      */
{
	int j;
	int k;
	int o;

	k = 0;
	j = -1;
	while (++j < NBR_PPOLY)
	{
		 if (j == NBR_PPOLY - 1)
		 	k = 0;
		 else
			k = j + 1;
		if (map->dot[j].x > 0 && map->dot[k].x > 0)
		{
			//printf("1w r : %d x = %f y = %f z = %f\n", j, map->dot[j].x, map->dot[j].y, map->dot[j].z);
			map->projx[j] = map->dot[j];
			//printf("1w r : %d x = %f y = %f z = %f\n", j, map->projx[j].x, map->projx[j].y, map->projx[j].z);
		}
		else if (map->dot[j].x > 0 && map->dot[k].x <= 0)
		{
			//printf("2w r : %d x = %f y = %f z = %f\n", j, map->dot[j].x, map->dot[j].y, map->dot[j].z);
			map->projx[j] = map->dot[j];
			// printf("2w r : %d x = %f y = %f z = %f\n", j, map->projx[j].x, map->projx[j].y, map->projx[j].z);
			if(k == NBR_PPOLY - 1)
				map->nbr_pprojx = NBR_PPOLY;
		}
		else if (map->dot[j].x <= 0 && map->dot[k].x > 0)
		{
			// printf("3w r : %d x = %f y = %f z = %f\n", j, map->dot[j].x, map->dot[j].y, map->dot[j].z);
			map->projx[j] = getnew_point(map->dot[j], map->dot[k]);
			// printf("						new point		%lf	%lf	%lf\n", map->projx[j].x, map->projx[j].y, map->projx[j].z);
			if(k == NBR_PPOLY - 1)
				map->nbr_pprojx = NBR_PPOLY;
			// printf("3w r : %d x = %f y = %f z = %f\n", j, map->projx[j].x, map->projx[j].y, map->projx[j].z);
		}
		else if(map->dot[j].x <= 0 && map->dot[k].x <= 0)
		{
			if(j == 0)
				o = map->nbr_pprojx - 1;
			else
				o = j - 1;
			if (map->dot[o].x > 0)
			{
				// printf("4w r : %d x = %f y = %f z = %f\n", j, map->dot[j].x, map->dot[j].y, map->dot[j].z);
				map->projx[j] = getnew_point(map->dot[j], map->dot[o]);
				// printf("4w r : %d x = %f y = %f z = %f\n", j, map->projx[j].x, map->projx[j].y, map->projx[j].z);
			}
		}
		printf("-----------------   %d   ----------------\n", j);
		printf("map->nbr_pprojx  = %d\n", map->nbr_pprojx);
	}
	if (map->nbr_pprojx != NBR_PPOLY)
		map->nbr_pprojx = map->nbr_p;
	// int i = -1;
	// while (++i < 4)
		// printf("Dot : %d x = %f y = %f z = %f\n", i, map->dot[i].x, map->dot[i].y, map->dot[i].z);
	// i = -1;
	// while (++i < 4)
		// printf("Sep points  |||   Dot : %d x = %f y = %f z = %f\n", i, map->projx[i].x, map->projx[i].y, map->projx[i].z);
} 


void 	Projxy(t_poly *map, t_input *data)
{
	int j = -1;
	while (++j < map->nbr_pprojx)
	{
			//printf("	----	PROXY		%lf	%lf	%lf\n", map->projx[j].x, map->projx[j].y, map->projx[j].z);
			map->projx[j].x = ((map->projx[j].y / map->projx[j].x) + X_VIEW / 2) * data->win_w / X_VIEW;
			map->projx[j].y = ((map->projx[j].z / map->projx[j].x) + Z_VIEW / 2) * data->win_h / Z_VIEW;
			//printf("point %d x = %lf y = %lf\n", j, map->projx[j].x, map->projx[j].y);
	}
}

int proj_2d(t_poly *map, t_input *data)
{
    while (map)
	{
		//printf("projecting poly nb: %d\n", i);
		separate_points(map);
		Projxy(map, data);
		poly_toboxes(data, map);
		ray_boxes(data, map);
		map = map->next;
	}
	return(1);
}