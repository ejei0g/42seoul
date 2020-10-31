/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 14:08:26 by jaeylee           #+#    #+#             */
/*   Updated: 2020/07/01 14:08:41 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*copy_s1;
	int		s1_len;
	int		i;

	i = 0;
	s1_len = ft_strlen(s1);
	copy_s1 = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (copy_s1 == NULL)
		return (NULL);
	while (i < s1_len)
	{
		*(copy_s1 + i) = *(s1 + i);
		i++;
	}
	*(copy_s1 + i) = '\0';
	return (copy_s1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	strlen;

	if (!s1 || !s2)
		return (NULL);
	strlen = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (strlen + 1));
	if (str == NULL)
		return (NULL);
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (str - strlen);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s);
	while (i < s_len + 1)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if ((substring = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (i < len && s[start])
		*(substring + i++) = *(s + start++);
	*(substring + i) = '\0';
	return (substring);
}
