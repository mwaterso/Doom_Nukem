/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing_list.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/22 23:36:02 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 17:43:07 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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

// void    free_line(t_line **line)
// {
//     t_line *tmp;
//     t_line *next;

//     tmp = *line;
//     while (tmp)
//     {
//         next = tmp->next;
//         ft_strdel(&(tmp->line));
//         free(tmp);
// 		tmp = next;
//     }
// 	*line = NULL;
// }

void			free_line(t_line **lst)
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

void    free_poly(t_poly **poly)
{
    t_poly *tmp;
    t_poly *next;

    tmp = *poly;
    while (tmp)
    {
        next = tmp->next;
        ft_strdel(&(tmp->tex));
        free(tmp);
		tmp = next;
    }
	*poly = NULL;
}


int		push_back(t_poly *new, t_poly **poly)
{
	t_poly *tmp;

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
	t_line	*new;

	if (!(new = (t_line *)malloc(sizeof(t_line))))
		return 0;
	if (!(new->line = ft_strdup(line)))
		return 0;
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
