/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:01:07 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/12 00:17:54 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line_bonus(int fd);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);
size_t	gnl_strlen(const char *s);
char	*gnl_strdup(const char *src);
char	*gnl_substr(char *s, unsigned int start, size_t len);

#endif