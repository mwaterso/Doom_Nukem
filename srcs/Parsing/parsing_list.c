/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:13:05 by beduroul          #+#    #+#             */
/*   Updated: 2020/02/27 17:13:07 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	error_file(int fd, char *av)
{
	errno = 0;
	read(fd, av, 0);
	if (errno != 0)
	{
		perror("error ");
		exit(0);
	}
}

void	free_line(t_line **lst)
{
	t_line		*head;
	t_line		*next;

	head = *lst;
	while (head != NULL)
	{
		next = head->next;
		if (head->line)
			ft_strdel(&head->line);
		ft_memdel((void **)&head);
		head = next;
	}
	*lst = NULL;
	head = NULL;
	next = NULL;
}

void	free_poly(t_poly **poly)
{
	t_poly		*tmp;
	t_poly		*next;

	tmp = *poly;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->tex)
			ft_strdel(&(tmp->tex));
		free(tmp);
		tmp = next;
	}
	*poly = NULL;
}

int		push_back(t_poly *new, t_poly **poly)
{
	t_poly		*tmp;

	if (*poly == NULL)
		*poly = new;
	else
	{
		tmp = *poly;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

int		creat_elem_l(char *line, int n_line, t_line **list)
{
	t_line		*new;

	if (!(new = (t_line *)malloc(sizeof(t_line))))
		return (0);
	if (!(new->line = ft_strdup(line)))
		return (0);
	new->next = NULL;
	new->n_line = n_line;
	if (*list == NULL)
		*list = new;
	else
	{
		new->next = *list;
		*list = new;
	}
	return (1);
}
