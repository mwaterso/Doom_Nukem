/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/05 16:44:11 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 12:54:05 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int		parser_error(t_data *data, char *line, char **tmp_tab, int index)
{
	int i;

	i = 0;
	if (ft_tablen((void **)tmp_tab) != data->map_data.width)
		{
			ft_putendl("Error size line");
			printf("%d\n", ft_tablen((void **)tmp_tab));
			ft_2dstrdel(&tmp_tab);
			ft_strdel(&line);
			while (i < index)
			{
				printf("%d\n", data->map_data.width);
				ft_free_tabint(&data->map_data.tab[i++], data->map_data.width);
			}
			free(data->map_data.tab);
			return (-1);
		}
	return (0);
}

int		fill_tab_int(t_data *data)
{
	char	**tmp_tab;
	char	**tmp;
	char	*line;
	t_index	index;

	index.i = 0;
	while(get_next_line(data->map_data.fd, &line))
	{
		if (!(data->map_data.tab[index.i] = malloc(sizeof(int *) * data->map_data.width)))
			return (-1);
		if (!(tmp_tab = ft_strsplit(line, '|')))
			return (-1);
		// if (ft_tablen((void **)tmp_tab) != data->map_data.width)
		// {
		// 	ft_putendl("Error size line");
		// 	ft_2dstrdel(&tmp_tab);
		// 	ft_strdel(&line);
		// 	return (-1);
		// }
		if (parser_error(data, line, tmp_tab, index.i) == -1)
			return (-1);
		index.j = 0;
		while (index.j < data->map_data.width)
		{
			if (!(data->map_data.tab[index.i][index.j] = malloc(sizeof(int) * data->map_data.z)))
				return (-1);
			if (!(tmp = ft_strsplit(tmp_tab[index.j], ',')))
				return (-1);
			if (ft_tablen((void **)tmp) != data->map_data.z)
			{
				ft_putendl("Error size block");
				ft_2dstrdel(&tmp);
				ft_strdel(&line);
				return (-1);
			}
			index.k = 0;
			while (index.k < data->map_data.z)
				data->map_data.tab[index.i][index.j][index.k++] = ft_atoi(tmp[index.k]);
			ft_2dstrdel(&tmp);
			index.j++;
		}
		ft_2dstrdel(&tmp_tab);
		ft_strdel(&line);
		index.i++;
	}
	return (0);
}

int		parser(t_data *data)
{
	char	*line;
	char	**tmp_tab;

	if (get_next_line(data->map_data.fd, &line))
	{
		if (!(tmp_tab = ft_strsplit(line, ';')))
			return (-1);
		if (ft_tablen((void**)tmp_tab) != 3)
			{
				ft_putendl("Error map value");
				ft_2dstrdel(&tmp_tab);
				ft_strdel(&line);
				return (-1);
			}
		data->map_data.height = ft_atoi(tmp_tab[0]);
		data->map_data.width = ft_atoi(tmp_tab[1]);
		data->map_data.z = ft_atoi(tmp_tab[2]);
		if (!(data->map_data.tab = malloc(sizeof(int **) * data->map_data.height)))
			return (-1);
		ft_2dstrdel(&tmp_tab);
		ft_strdel(&line);
	}
	if (fill_tab_int(data) == -1)
		return (-1);
	// while(get_next_line(data->map_data.fd, &line))
	// {
	// 	if (!(data->map_data.tab[i] = malloc(sizeof(int *) * data->map_data.width)))
	// 		return (-1);
	// 	tmp_tab = ft_strsplit(line, '|');
	// 	if (ft_tablen((void **)tmp_tab) != data->map_data.width)
	// 	{
	// 		ft_putendl("Error size line");
	// 		ft_2dstrdel(&tmp_tab);
	// 		return (-1);
	// 	}
	// 	j = 0;
	// 	while (j < data->map_data.width)
	// 	{
	// 		if (!(data->map_data.tab[i][j] = malloc(sizeof(int) * data->map_data.z)))
	// 			return (-1);
	// 		tmp = ft_strsplit(tmp_tab[j], ',');
	// 		if (ft_tablen((void **)tmp) != data->map_data.z)
	// 		{
	// 			ft_putendl("Error size block");
	// 			ft_2dstrdel(&tmp);
	// 			return (-1);
	// 		}
	// 		k = 0;
	// 		while (k < data->map_data.z)
	// 		{
	// 			data->map_data.tab[i][j][k] = ft_atoi(tmp[k]);
	// 			k++;
	// 		}
	// 		ft_2dstrdel(&tmp);
	// 		j++;
	// 	}
	// 	ft_2dstrdel(&tmp_tab);
	// 	i++;
	// }
	// int i = 0;
	// int j = 0;
	// int k = 0;
	// while (i < data->map_data.height)
	// {
	// 	j = 0;
	// 	while (j < data->map_data.width)
	// 	{
	// 		k = 0;
	// 		while (k < data->map_data.z)
	// 		{
	// 			printf("%d ", data->map_data.tab[i][j][k]);
	// 			k++;
	// 		}
	// 		printf("| ");
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
	return (0);
}
