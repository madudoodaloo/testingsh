/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:44:25 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/19 23:58:04 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_intmin(char *str)
{
	int	i;

	str[1] = '2';
	i = -147483648;
	return (i);
}

static size_t	ft_digits(int n)
{
	size_t	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
		i++;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	size;

	size = ft_digits(n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = 48;
	if (n < 0)
	{
		str[0] = '-';
		if (n == -2147483648)
			n = ft_intmin(str);
		n = -n;
	}
	str[size] = '\0';
	while (n > 0)
	{
		str[--size] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}

char	**copy_matrix(char **src)
{
	char	**dst;
	int		i;

	i = 0;
	while (src[i] != NULL)
		i++;
	dst = (char **)safe_malloc(sizeof(char *) * (i + 1));
	if (!dst)
		return (NULL);
	i = -1;
	while (src[++i])
		dst[i] = ft_strdup(src[i]);
	dst[i] = NULL;
	return (dst);
}
