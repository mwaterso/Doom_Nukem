/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mtl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:02:20 by beduroul          #+#    #+#             */
/*   Updated: 2020/02/18 20:02:21 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void    sort_mtllib(char *line, t_mtl *mlt, t_input *data)
{
    int i;

    i = -1;
    while (line[++i])
        if (line[i] == ' ')
            break ;
    if (!(mlt->tex.tab = (int *)mlx_xpm_file_to_image(data->mlx_ad, line + (i + 1),
		&mlt->tex.width, &mlt->tex.height)))
		return (0);
}

int     parse_mtl(t_poly **poly, t_input *data, t_line *list)
{
    while (list)
    {
        if (ft_strnequ_word(list->line, "Ka ", 3))
            sort_color(list->line, &((*poly)->mtl.ka));
        if (ft_strnequ_word(list->line, "Kd ", 3))
            sort_color(list->line, &((*poly)->mtl.kd));
        if (ft_strnequ_word(list->line, "mtllib ", 7))
            sort_mtllib(list->line, &((*poly)->mtl), data);
        
        list = list->next;
    }
}

int     p_mtl_loop(t_input *data, int fd, t_poly *poly)
{
	t_line *list;
	int n_line;
	char *line;
	int i;

	i = 0;
	n_line = 0;
	list = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if(!(creat_elem_l(line, n_line, &list)))
			return 0;
		n_line++;
		ft_strdel(&line);
	}
	ft_strdel(&line);
    reverse_l(&list);
    
    while (list)
    {
        printf("%s\n", list->line);
        list = list->next;
    }
    (void)poly, (void)data;
	return i;
}

void    sort_mtl(t_input *data, t_poly **poly, char *file)
{
    int		fd;
    int     i;
    char    *l_file;

	(void)data;
    i = -1;
    while (file[++i])
        if (file[i] == ' ')
            break ;
    if (!(l_file = ft_strjoin("Object/", file + (i + 1))))
        return ;
	if ((fd = open(l_file, O_RDONLY)) < 1)
		return ;
    error_file(fd, file);
    if (!(p_mtl_loop(data, fd, poly)))
        return ;

    ft_strdel(&l_file);
}
