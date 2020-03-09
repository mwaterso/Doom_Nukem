/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 17:42:01 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/03/06 19:29:15 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void rev_moove(t_input *data, int way)
{
    ("Rev moove\n");
    if (way == KEY_UP)
		mapmoveallp(data->map, (t_fdot){.x = 1, .y = 0, .z = 0});
    if (way == KEY_DOWN)
		mapmoveallp(data->map, (t_fdot){.x = -1, .y = 0, .z = 0});
    if (way == KEY_RIGHT)
		mapmoveallp(data->map, (t_fdot){.x = 0, .y = -1, .z = 0});
    if (way == KEY_LEFT)
		mapmoveallp(data->map, (t_fdot){.x = 0, .y = 1, .z = 0});
		//redefinevector(data->map);
}

void moove(t_input *data, int way)
{
    if (way == KEY_UP)
		mapmoveallp(data->map, (t_fdot){.x = -1, .y = 0, .z = 0});
    if (way == KEY_DOWN)
		mapmoveallp(data->map, (t_fdot){.x = 1, .y = 0, .z = 0});
    if (way == KEY_RIGHT)
		mapmoveallp(data->map, (t_fdot){.x = 0, .y = 1, .z = 0});
    if (way == KEY_LEFT)
		mapmoveallp(data->map, (t_fdot){.x = 0, .y = -1, .z = 0});
    if (check_colli(data->map))
        rev_moove(data, way);
		//redefinevector(data->map);
}


void mapmoveallp(t_poly *poly, t_fdot incr)
{
    int i;
    t_poly *gones;

    gones = poly;
    while(gones)
    {
		i = -1;
        while(++i < gones->nbr_p)
        {
			gones->dot[i].x += incr.x;
            gones->dot[i].y += incr.y;
            gones->dot[i].z += incr.z;
			gones->rotx[i].x += incr.x;
            gones->rotx[i].y += incr.y;
            gones->rotx[i].z += incr.z;
		}
		gones->d = -(gones->a * gones->dot[0].x + gones->b * gones->dot[0].y + gones->c * gones->dot[0].z);
        gones = gones->next;
    }
}

void maprotateallp(t_poly *poly, t_fdot rot, t_input *data)
{
    int i;
    t_poly *gones;
    gones = poly;
            
    while(gones)
    {
    i = -1;
        while(++i < poly->nbr_p)
        {
		//printf("MAP: gones %d %f %f %f\n", gones->nbr_p, gones->rotx[i].x, gones->rotx[i].y, gones->rotx[i].z);
            if (rot.y)
            {
                    gones->dot[i] = data->angley == 0 ? gones->rotx[i] : ApplyMatPoint(define_yRotMat(data->angley), gones->rotx[i]);
                    //gones->vAB = ApplyMatPoint(define_yRotMat(data->angley), gones->vAB);
                   //gones->vBC = ApplyMatPoint(define_yRotMat(data->angley), gones->vBC);
          //          printf("roty\n");
            }
            else 
            {
                if (rot.z == 1)
                    gones->rotx[i] = ApplyMatPoint(data->rotz, gones->rotx[i]);
                else if (rot.z == -1)
                    gones->rotx[i] = ApplyMatPoint(data->minrotz, gones->rotx[i]);
                data->nbrtour = 1;
            }
                
		//printf("-------%d-------------------- gones %d %f %f %f\n", i, gones->nbr_p, gones->dot[i].x, gones->dot[i].y, gones->dot[i].z);
        }
       // printf("%p\n", gones);
        gones = gones->next;
    }

		redefinevector(data->map);
}