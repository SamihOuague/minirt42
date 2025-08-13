/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 21:51:39 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/12 23:55:52 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

char	*get_next_line(int fd)
{
	char	buf[2];
	char	*res;
	char	*tmp;

	tmp = NULL;
	res = NULL;
	ft_bzero(buf, 2);
	while (read(fd, buf, 1))
	{
		if (res == NULL)
			res = ft_strdup("");
		if (res == NULL)
			return (res);
		tmp = res;
		res = ft_strjoin(res, buf);
		free(tmp);
		tmp = NULL;
		if (res == NULL)
			return (NULL);
		if (buf[0] == '\n')
			break ;
	}
	return (res);
}

int	ft_space_to_null(char *str, int *size)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 1;
	k = 0;
	while (*(str + i) != '\0')
	{
		if (*(str + i) == ' ' || *(str + i) == '\t')
		{
			*(str + i) = '\0';
			if (k == 1 && (++j))
				k = 0;
		}
		else
			k = 1;
		i++;
	}
	*size = j + (i != 0);
	return (i);
}

char	**ft_fast_split(char *str)
{
	char	**split;
	int		size;
	int		k;
	int		i;

	i = 0;
	split = NULL;
	k = ft_space_to_null(str, &size);
	split = malloc(sizeof(char *) * size);
	if (split == NULL)
		return (NULL);
	ft_bzero(split, sizeof(char *) * size);
	size = 0;
	while (i < k)
	{
		if (*(str + i) != '\0')
		{
			split[size] = (str + i);
			i += ft_strlen((str + i)) - 1;
			size++;
		}
		i++;
	}
	return (split);
}

double	ft_to_double(char *nbr)
{
	double	right;
	long	left;
	char	*dot;	
	int		n;

	n = (*nbr) == '-';
	dot = ft_strchr(nbr, '.');
	if (dot == NULL)
		return ((double)ft_atoi(nbr));
	left = ft_atoi(nbr + n);
	right = ft_atoi(dot + 1);
	while (right >= 1)
		right = right / 10;
	right = ((double)left) + right;
	if (n)
		right *= -1;
	return (right);
}

char	*ft_to_space(char *str)
{
	int	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		if (*(str + i) == ',')
			*(str + i) = ' ';
		i++;
	}
	return (str);
}
