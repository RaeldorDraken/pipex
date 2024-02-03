/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pscript.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:15:41 by eros-gir          #+#    #+#             */
/*   Updated: 2022/07/23 14:28:34 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipexlib.h"

char	*ft_pscript(const char *s)
{
	char	*sr;
	size_t	len;
	size_t	len2;

	len = ft_strlen(s);
	len2 = 0;
	sr = ft_calloc(sizeof(char), len + 1);
	if (!sr)
		return (0);
	len = 0;
	while (s[len])
	{
		if ((s[len] == '\'' || s[len] == '\"') && s[len - 1] == '\\')
			len2 --;
		else if (s[len] == '\'' || s[len] == '\"')
			len ++;
		sr[len2++] = s[len++];
	}
	sr[len2] = '\0';
	return (sr);
}
