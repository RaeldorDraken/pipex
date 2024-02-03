/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_psplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:19:42 by eros-gir          #+#    #+#             */
/*   Updated: 2023/05/01 10:55:14 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipexlib.h"

size_t	ft_pstrnum(const char *s, char c)
{	
	size_t	len;
	size_t	numb;
	int		quotes;

	set_vars(&len, &numb, &quotes);
	while (s[len])
	{
		while (s[len] == c || ((s[len] == '\'' || s[len] == '\"')
				&& s[len - 1] != '\\'))
		{
			if ((s[len] == '\'' || s[len] == '\"') && s[len - 1] != '\\')
				numb += add_numb(quotes++);
			len++;
		}
		if (s[len] && (s[len] != c && quotes <= 0))
			numb++;
		while (s[len] != 0 && s[len] != c)
		{
			if ((s[len] == '\'' || s[len] == '\"') && s[len - 1] != '\\')
				quotes --;
			len++;
		}
	}
	return (numb);
}

char	*ft_pstrset2(const char *s, char c)
{
	char	*sr;
	size_t	len;
	size_t	len2;

	len = 0;
	len2 = 0;
	while (s[len] != c && (s[len - 1] == '\\' && s[len] == c) && s[len++])
		len2++;
	sr = ft_calloc(sizeof(char), len + 1);
	if (!sr)
		return (0);
	len = 0;
	while (s[len])
	{
		if (s[len] == c && s[len - 1] != '\\')
			break ;
		else if (s[len] == c && s[len - 1] == '\\')
			len2 --;
		sr[len2++] = s[len++];
	}
	sr[len2] = '\0';
	return (sr);
}

char	*ft_pstrset(const char *s, char c)
{
	char	*sr;
	size_t	len;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	sr = ft_calloc(sizeof(char), len + 1);
	if (!sr)
		return (0);
	len = 0;
	while (s[len] != c && s[len])
	{
		sr[len] = s[len];
		len++;
	}
	sr[len] = '\0';
	return (sr);
}

char	*ft_pgetset(const char *s, char c, int qt)
{
	if (qt == 1)
		return (ft_pstrset2(s, '\''));
	else if (qt == 2)
		return (ft_pstrset2(s, '\"'));
	else if (qt == 3)
		return (ft_pscript(s));
	return (ft_pstrset(s, c));
}

char	**ft_psplit(const char *s, char c, t_pipex *pobj, int quotes)
{
	char	**strings;
	size_t	n;
	size_t	strn;

	n = 0;
	strn = ft_pstrnum(s, c);
	strings = ft_calloc(sizeof(char **), strn + 1);
	while (n < strn)
	{
		quotes = ft_check_quotes(*s);
		if (quotes != 3)
		{
			while (*s == c || *s == '\'' || *s == '\"')
			{
				quotes = ft_check_quotes(*s);
				s++;
			}
		}
		strings[n] = ft_pgetset(s, c, quotes);
		ft_string_error(strings, n, pobj);
		printf ("%zu: %s\n", n, strings[n]);
		s += ft_strlen(strings[n++]);
	}
	return (strings);
}
