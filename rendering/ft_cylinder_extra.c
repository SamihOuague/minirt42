/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:07:06 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/11 23:07:15 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_cylinder_shape(t_shape **shape)
{
	if (shape == NULL || *shape == NULL)
		return ;
	(**shape).has_inter = &ft_cylinder_intersection;
}
