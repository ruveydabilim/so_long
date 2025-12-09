/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:04:45 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/11 16:57:41 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char				*joined;
	unsigned int		t_len;
	unsigned int		i;
	unsigned int		j;

	if (!s1 || !s2)
		return (NULL);
	t_len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	joined = (char *)malloc(t_len + 2);
	if (!joined)
		return (NULL);
	while (s1[i])
		joined[j++] = s1[i++];
	i = 0;
	while (s2[i])
		joined[j++] = s2[i++];
	joined[j] = ' ';
	joined[j + 1] = '\0';
	return (joined);
}
