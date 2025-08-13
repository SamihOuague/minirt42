/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 04:35:48 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/13 23:05:03 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_extract_line(char *line, t_scene *scene)
{
	char	**split;
	int		size;

	split = ft_fast_split(line);
	if (split == NULL)
	{
		(*scene).error = -1;
		return ;
	}
	size = ft_len(split);
	if (size > 6 || size < 3)
	{
		(*scene).error = ft_len(split) != 0;
		free(split);
		return ;
	}
	(*scene).error = ft_init_elements(split, scene);
	free(split);
}

void	ft_free_content(void *content)
{
	t_shape	*shape;

	if (content == NULL)
		return ;
	shape = (t_shape *)content;
	free((*shape).object);
	free(shape);
}

void	ft_set_scene(t_scene *scene)
{
	(*scene).shapes = NULL;
	(*scene).error = 0;
	(*scene).ambient = 0;
	(*scene).color = ft_vec3(0, 0, 0);
	ft_bzero((*scene).cla, sizeof(int) * 3);
}
