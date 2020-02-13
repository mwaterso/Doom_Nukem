/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   object_list.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/14 00:02:34 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/14 00:02:36 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void             poly_rev(t_poly **poly) 
{ 
    t_poly    *prev; 
    t_poly    *current; 
    t_poly    *next; 

	current = *poly;
	next = NULL;
	prev = NULL;
    while (current)
	{ 
        next = current->next;
        current->next = prev; 
        prev = current; 
        current = next; 
    } 
    *poly = prev; 
} 

void			push_front_obj(t_object *new, t_object **obj)
{
	if (!obj)
		*obj = new;
	else
	{
		new->next = *obj;
		*obj = new;
	}
}

void             reverse(t_object **obj) 
{ 
    t_object    *prev; 
    t_object    *current; 
    t_object    *next; 

	current = *obj;
	next = NULL;
	prev = NULL;
    while (current)
	{ 
        next = current->next;
        current->next = prev; 
        prev = current; 
        current = next; 
    } 
    *obj = prev; 
} 
