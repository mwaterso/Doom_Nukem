/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   matrix.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/17 18:00:04 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/22 14:21:21 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"


t_3x3matrix define_yRotMat(float a)
{
    t_3x3matrix Ry;

    Ry.a1 = cos(a);
    Ry.a2 = 0;
    Ry.a3 = sin(a);

    Ry.b1 = 0;
    Ry.b2 = 1;
    Ry.b3 = 0;

    Ry.c1 = - sin(a);
    Ry.c2 = 0;
    Ry.c3 = cos(a);
    return  (Ry);
}

t_3x3matrix define_minyRotMat()
{
    t_3x3matrix Ry;
    Ry.a1 = cos(-ROTZ);
    Ry.a2 = 0;
    Ry.a3 = sin(-ROTZ);

    Ry.b1 = 0;
    Ry.b2 = 1;
    Ry.b3 = 0;

    Ry.c1 = - sin(-ROTZ);
    Ry.c2 = 0;
    Ry.c3 = cos(-ROTZ);
    return  (Ry);
}

t_3x3matrix define_zRotMat()
{
    t_3x3matrix Rz;
    Rz.a1 = cos(ROTZ);
    Rz.a2 = -sin(ROTZ);
    Rz.a3 = 0;

    Rz.b1 = sin(ROTZ);
    Rz.b2 = cos(ROTZ);
    Rz.b3 = 0;

    Rz.c1 = 0;
    Rz.c2 = 0;
    Rz.c3 = 1;
    return  (Rz);
}

t_3x3matrix define_minzRotMat()
{
    t_3x3matrix Rz;
    Rz.a1 = cos(-ROTZ);
    Rz.a2 = -sin(-ROTZ);
    Rz.a3 = 0;

    Rz.b1 = sin(-ROTZ);
    Rz.b2 = cos(-ROTZ);
    Rz.b3 = 0;

    Rz.c1 = 0;
    Rz.c2 = 0;
    Rz.c3 = 1;
    return  (Rz);
}


t_fdot ApplyMatPoint(t_3x3matrix matrix, t_fdot point)
{
    t_fdot newPoint;

    newPoint.x = matrix.a1 * point.x + matrix.a2 * point.y + matrix.a3 * point.z;
    newPoint.y = matrix.b1 * point.x + matrix.b2 * point.y + matrix.b3 * point.z;
    newPoint.z = matrix.c1 * point.x + matrix.c2 * point.y + matrix.c3 * point.z;
    return  (newPoint);
}