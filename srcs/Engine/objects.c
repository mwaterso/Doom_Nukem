/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   objects.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/22 13:40:16 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/26 16:32:20 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


#include "doom.h"

void printobj(t_object *obj, t_input *data)
{
	int i;
	int ret;
	i = -1;
    while (obj)
	{
		i++;
		//while(++i < 3)
		//	printf("%d  projection : %lf  %lf  %lf\n", i, obj->dot[i].x, obj->dot[i].y, obj->dot[i].z);
		separate_points(obj->poly);
		ret = Projxy(obj->poly, data);
		if (ret)
		{
			poly_toboxes(data, obj->poly);
			ray_boxes(data, obj->poly);
		}
		else
		{
			printf("non print : %d\n", i);
		}
		
		obj = obj->next;
	}
	//printf("%p		%p\n", data->im.tab, data->im.ad);
	mlx_put_image_to_window(data->mlx_ad, data->win_ad, data->im.ad, 0, 0);
	return(1);
}

