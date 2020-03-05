/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:23:01 by beduroul          #+#    #+#             */
/*   Updated: 2020/03/04 20:23:03 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	push_front_obj(t_object *new, t_object **obj)
{
	if (!obj)
		*obj = new;
	else
	{
		new->next = *obj;
		*obj = new;
	}
}

void	push_front_pol(t_poly *new, t_poly **poly)
{
	if (!poly)
		*poly = new;
	else
	{
		new->next = *poly;
		*poly = new;
	}
}

void	reverse_p(t_poly **poly)
{
	t_poly		*prev;
	t_poly		*current;
	t_poly		*next;

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

void	reverse_l(t_line **list)
{
	t_line		*current;
	t_line		*prev;
	t_line		*next;

	current = *list;
	next = NULL;
	prev = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*list = prev;
}

void	reverse_o(t_object **obj)
{
	t_object	*current;
	t_object	*prev;
	t_object	*next;

	current = *obj;
	next = NULL;
	prev = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*obj = prev;
}
