/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_others.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 04:14:53 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/10 04:16:28 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	ft_float_checker(char *nbr)
{
	int	i;
	int	n;

	i = *nbr == '-';
	n = 0;
	if (*nbr == '.')
		return (1);
	while (*(nbr + i) != '\0')
	{
		if (*(nbr + i) == '.')
		{
			if (n == 1 || *(nbr + i + 1) == '\0')
				return (1);
			n++;
		}
		else if (!ft_isdigit(*(nbr + i)))
			return (1);
		i++;
	}
	return (0);
}

void	ft_insert_object(t_shape *object, t_scene *scene)
{
	t_list	*lst;

	if ((*scene).shapes == NULL)
	{
		lst = ft_lstnew(object);
		if (lst == NULL)
		{
			(*scene).error = -1;
			return ;
		}
		(*scene).shapes = lst;
		return ;
	}
	ft_lstadd_front(&(*scene).shapes, ft_lstnew(object));
}

int	ft_init_elements(char **split, t_scene *scene)
{
	if (!ft_strncmp(split[0], "C", 2))
		return (ft_init_camera(split, scene));
	else if (!ft_strncmp(split[0], "L", 2))
		return (ft_init_light(split, scene));
	else if (!ft_strncmp(split[0], "A", 2))
		return (ft_init_ambient(split, scene));
	else if (!ft_strncmp(split[0], "cy", 3))
		return (ft_init_cylinder(split, scene));
	else if (!ft_strncmp(split[0], "sp", 3))
		return (ft_init_sphere(split, scene));
	else if (!ft_strncmp(split[0], "pl", 3))
		return (ft_init_plan(split, scene));
	return (1);
}

void	ft_init_scene(int fd, t_scene *scene)
{
	char	*str;

	str = get_next_line(fd);
	while (str != NULL)
	{
		if (str != NULL)
		{
			if (*(str + ft_strlen(str) - 1) == '\n')
				*(str + ft_strlen(str) - 1) = '\0';
			ft_extract_line(str, scene);
			free(str);
			if ((*scene).error)
				break ;
		}
		str = get_next_line(fd);
	}
	return ;
}
