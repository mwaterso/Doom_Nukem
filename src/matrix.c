/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   matrix.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/17 18:00:04 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/28 14:25:02 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

t_3x3matrix define_xRotMat()
{
    t_3x3matrix Rx;
    Rx.a1 = 1;
    Rx.a2 = 0;
    Rx.a3 = 0;

    Rx.b1 = 0;
    Rx.b2 = cos(ROTX);
    Rx.b3 = -sin(ROTX);

    Rx.c1 = 0;
    Rx.c2 = sin(ROTX);
    Rx.c3 = cos(ROTX);
    return  (Rx);
}

t_3x3matrix define_yRotMat()
{
    t_3x3matrix Ry;
    Ry.a1 = cos(ROTY);
    Ry.a2 = 0;
    Ry.a3 = sin(ROTY);

    Ry.b1 = 0;
    Ry.b2 = 1;
    Ry.b3 = 0;

    Ry.c1 = - sin(ROTY);
    Ry.c2 = 0;
    Ry.c3 = cos(ROTY);
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

t_fdot ApplyMatPoint(t_3x3matrix matrix, t_fdot point)
{
    t_fdot newPoint;

    newPoint.x = matrix.a1 * point.x + matrix.a2 * point.y + matrix.a3 * point.z;
    newPoint.y = matrix.b1 * point.x + matrix.b2 * point.y + matrix.b3 * point.z;
    newPoint.z = matrix.c1 * point.x + matrix.c2 * point.y + matrix.c3 * point.z;
    return  (newPoint);
}