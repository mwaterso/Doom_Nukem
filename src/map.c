/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 17:42:01 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 18:08:39 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

void mapmoveallp(t_poly *poly, t_fdot incr)
{
    int i;
    t_poly *gones;

    i = -1;
    gones = poly;
    //printf("Mapmoveallp  %d\n", nbrpoly);
    while(gones)
    {
        while(++i < gones->nbr_p)
        {   
            printf("i = %d\n", i);         
            printf("MAP: %f %f %f\n", poly->dot[i].x, poly->dot[i].y, poly->dot[i].z);
            gones->dot[i].x += incr.x;
            gones->dot[i].y += incr.y;
            gones->dot[i].z += incr.z;
            printf("MAP: %f %f %f\n", gones->dot[i].x, gones->dot[i].y, gones->dot[i].z);
        }
        gones = gones->next;
    }
}

void maprotateallp(t_poly *poly, t_fdot rot, t_input *data)
{
    int i;
    t_poly *gones;

    gones = poly;
    i = -1;
    while(gones)
    {
        while(++i < poly->nbr_p)
        {
            if (rot.y)
                ApplyMatPoint(data->roty, poly->dot[i]);
            else if (rot.z)
                ApplyMatPoint(data->rotz, poly->dot[i]);
        }
        gones = gones->next;
    }
}