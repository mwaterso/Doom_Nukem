/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   math.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/21 14:43:50 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 18:19:16 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

t_fdot getvect(t_fdot a, t_fdot b)
{
    //printf("vectorial product\n");
    return((t_fdot){.x = b.x - a.x, .y = b.y - a.y, .z = b.z - a.z});
}

double get3ddist(t_fdot a, t_fdot b)
{
    return(sqrtf(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2)));
}


t_fdot vectorial_product(t_fdot a, t_fdot b)
{
    //printf("vectorial product\n");
    t_fdot u;

    u.x = a.y * b.z - a.z * b.y;
    u.y = a.z * b.x - a.x * b.z;
    u.z = a.x * b.y - a.y * b.x;
    return (u);
}

void get_plans(t_poly *poly)
{
    t_fdot vectu;
    //printf("poly = %p\nnbr points = %d\n point1 x = %f y = %f z = %f", poly, poly->nbrpoly, poly->finaldot3d[0].x, poly->finaldot3d[0].y, poly->finaldot3d[0].z);
    while (poly)
    {
        vectu = vectorial_product(getvect(poly->dot[0], poly->dot[1]), getvect(poly->dot[0], poly->dot[2]));

        poly->a = vectu.x;
        poly->b = vectu.y;
        poly->c = vectu.z;

        poly->d = -(poly->a * poly->dot[0].x + poly->b * poly->dot[0].y + poly->c * poly->dot[0].z);

	    // printf("PLAN ||| %lf	%lf	%lf	%lf\n", poly->a, poly->b, poly->c, poly->d);
	    // printf("PLAN ||| %lf	%lf	%lf\n", poly->finaldot3d[0].x, poly->finaldot3d[0].y, poly->finaldot3d[0].z);
	    // printf("PLAN ||| %lf	%lf	%lf\n", poly->finaldot3d[1].x, poly->finaldot3d[1].y, poly->finaldot3d[1].z);
	    // printf("PLAN ||| %lf	%lf	%lf\n", poly->finaldot3d[2].x, poly->finaldot3d[2].y, poly->finaldot3d[2].z);
        //poly->areaabc = get3ddist(poly->finaldot3d[0], poly->finaldot3d[1]) * get3ddist(poly->finaldot3d[0], poly->finaldot3d[2]) ;// / 2;
		poly = poly->next;
    }
}