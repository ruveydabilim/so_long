/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:13:28 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/12 00:17:31 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strchr(const char *s, int c)
{
	char	*temp_s;
	int		i;

	i = 0;
	temp_s = (char *)s;
	while (temp_s[i] != (unsigned char)c && temp_s[i])
		i++;
	if ((unsigned char)c != '\0' && !temp_s[i])
		return (NULL);
	return ((char *)s + i);
}

char	*gnl_strdup(const char *src)
{
	int		i;
	char	*c;

	i = 0;
	while (src[i])
		i++;
	c = (char *)malloc(sizeof(char) * i + 1);
	if (!c)
		return (NULL);
	i = 0;
	while (src[i])
	{
		c[i] = src[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char				*joined;
	unsigned int		t_len;
	unsigned int		i;
	unsigned int		j;

	t_len = gnl_strlen(s1) + gnl_strlen(s2);
	if (t_len == 0)
		return (NULL);
	i = 0;
	j = 0;
	joined = (char *)malloc(t_len + 1);
	if (!joined)
		return (NULL);
	while (s1 != NULL && s1[i])
		joined[j++] = s1[i++];
	i = 0;
	while (s2 != NULL && s2[i])
		joined[j++] = s2[i++];
	joined[j] = '\0';
	free(s1);
	free(s2);
	return (joined);
}

char	*gnl_substr(char *s, unsigned int start, size_t len)
{
	char			*t;
	size_t			i;
	size_t			len_s;

	if (!s)
		return (NULL);
	len_s = gnl_strlen(s);
	i = 0;
	if (len_s <= start)
		return (NULL);
	if (len > len_s - start)
		len = len_s - start;
	t = (char *)malloc(len + 1);
	if (!t)
		return (NULL);
	while (s[start + i] && i < len)
	{
		t[i] = s[start + i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
