/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:12:11 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/11 19:08:44 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_create_image(t_elt *params)
{
	t_vec3	matrix[3];
	t_vec3	xy;
	int	k;
	int	size;
	t_vec3	vector;
	double	fov;
	t_ray	ray;
	int	pixel;

	k = 0;
	fov = (*params).scene.camera.fov;
	size = (*params).width * (*params).height;
	ft_lookAt(matrix, (*params).scene.camera.direction);
	while (k < size)
	{
		pixel = 0;
		xy.x = k % (*params).width;
		xy.y = k / (*params).width;
		vector = ft_vec3((*params).aspect_r * ((((double)xy.x + 0.5)/(*params).width) * 2 - 1) * tan(ft_radian(fov / 2)), (((double)xy.y + 0.5)/(*params).height * 2 - 1) * tan(ft_radian(fov / 2)), 1);
		vector = transform_ray(vector, matrix);
		ft_init_ray(&ray, vector, (*params).scene.camera);
		if (ft_has_intersection((*params).scene.shapes, &ray, NULL))
			pixel = ft_light(&ray, &(*params).scene);
		ft_pixel_put(&(*params).data_addr, xy.x, (*params).height - 1 - xy.y, (*params).size_line, (*params).bpp, pixel);
		k++;
	}
}

int	main(int argc, char **argv)
{
	t_elt	params;
	t_ray	ray;

	params.height = 800;
	params.width = 1200;
	params.aspect_r = (double)params.width/(double)params.height;
	if (argc != 2)
		return (1);
	else if (ft_minirt_init(argv[1], &params))
		return (1);
	params.mlx = mlx_init();
	if (params.mlx == NULL)
	{	
		ft_lstclear(&params.scene.shapes, &ft_free_content);
		return (1);
	}	
	params.win = mlx_new_window(params.mlx, params.width, params.height, "MiniRT");
	params.img_ptr = mlx_new_image(params.mlx, params.width, params.height);
	params.data_addr = mlx_get_data_addr(params.img_ptr, &params.bpp, &params.size_line, &params.endian);
	ft_create_image(&params);	
	ft_run_loop(&params, params.width, params.height);
	return (0);
}
