/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing_tex.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 17:13:23 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 17:13:25 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void    free_texlst(t_lstex **tex)
{
    t_lstex *tmp;
    t_lstex *next;

    tmp = *tex;
    while (tmp)
    {
        next = tmp->next;
        ft_strdel(&(tmp->long_name));
        free(tmp);
		tmp = next;
    }
	*tex = NULL;
}

int		push_back_tex(t_lstex *new, t_lstex **lst)
{
	t_lstex *tmp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

int init_lsttex(t_poly *poly, t_lstex **lst, t_input data)
{
	(void)data;
	t_lstex *new;

	if (!(new = (t_lstex *)malloc(sizeof(t_lstex))))
		return 0;
	new->next = NULL;
	if (!(new->name = ft_strdup(poly->tex)))
		return 0;
	if (!(new->long_name = ft_strjoin("texture/", new->name)))
		return 0;
	if (!(new->tex.im.ad = mlx_xpm_file_to_image(data.mlx_ad, new->long_name,
		&new->tex.width, &new->tex.height)))
		return (0);
	push_back_tex(new, lst);
	return 1;
}

t_lstex             *tex_cmp(char *tex, t_lstex *lst)
{
	if (!lst)
		return NULL;
	while (lst)
	{
		if (!(ft_strcmp(lst->name, tex))){
			return lst;}
		lst = lst->next;
	}
	return NULL;
}

int				load_tex(t_poly **poly, t_input data)
{
	t_lstex	*lst;
	t_poly	*tmp;

	tmp = *poly;
	lst = NULL;
	while (tmp)
	{
		if (!(tex_cmp(tmp->tex, lst)))
		{
			if(!(init_lsttex(tmp, &lst, data)))
				return 0;
		}
		tmp->tex_tab = tex_cmp(tmp->tex, lst)->tex;
		tmp = tmp->next;
	}
	free_texlst(&lst);
	return 1;
}